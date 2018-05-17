#include <rqc.h>
#include <readregfile.h>
#include <qc_list.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>


//第一个参数为收集的路径,64个字符：/home/acenter/src/rqc/reg
//第二个参数为发送的路径,64个字符：/home/acenter/src/rqc/send
//第三个参数为日志的路径,64个字符：/home/acenter/src/rqc/log
int main(int argc,char **argv)
{
    //定义收集目录
    char recv_path[64];
    //定义质控后的发送目录
    char send_path[64];
    //定义日志存放路径
    char log_path[64];
    
    
    //定义格式检查日志文件
    char formatlogpath[64];
    //定义质控日志文件
    char qclogpath[64];
    
    strcpy(recv_path,argv[1]);
    strcpy(send_path,argv[2]);
    strcpy(log_path,argv[3]);
    
    //定义区域站文件名模版
    char awscard[]="Z_SURF_C_B\?\?\?-REG_*_O_AWS_FTM.txt";
    
    while(1)
     {
        //获取当前时间
        time_t time_file;//time_t就是long int 类型
        struct tm  *tm_file;//存储时间的结构体
        time_file= time(NULL);
        tm_file = localtime(&time_file);//获取了时间结构体
        
        //置空日志文件
        memset(&formatlogpath,0,64);
        memset(&qclogpath,0,64);
        
        //根据时间定义日志文件
        sprintf(formatlogpath,"%s/format-%d%02d%02d%02d.log",log_path,tm_file->tm_year+1900,tm_file->tm_mon+1,tm_file->tm_mday,tm_file->tm_hour);
        sprintf(qclogpath,"%s/qc-%d%02d%02d%02d.log",log_path,tm_file->tm_year+1900,tm_file->tm_mon+1,tm_file->tm_mday,tm_file->tm_hour);
        
        //记录格式检查错误日志
        FILE *format_fp;
        if((format_fp=fopen(formatlogpath,"a+"))==NULL)
         {
            printf("open format_log faild \n");
            return 0;
         }
    
        //记录质量控制错误日志
        FILE *qc_fp;
        if((qc_fp=fopen(qclogpath, "a+"))==NULL)
        {
           printf("open qc_log faild \n");
           return 0;
        }
        
        //读取收集目录
        DIR *recv_dp=opendir(recv_path);
        //遍历目录内的所有文件
        struct dirent *recv_entry;
        while((recv_entry=readdir(recv_dp))!=NULL)
         {
            //定义全路径
            char recv_filename[128];
            sprintf(recv_filename,"%s/%s",recv_path,recv_entry->d_name);
            
            //判断读取的文件类型
            struct stat statbuf;
            //获取文件的类型
            lstat(recv_filename,&statbuf);
            
            
            //如果是一个文件而且文件名符合模版则进行文件处理
            if(S_ISREG(statbuf.st_mode))
             {
                 if(match(recv_entry->d_name,awscard))
                 {
                    /*解析这个文件到站级数据结构,
                    将解析的格式错误台站信息保存到日志文件*/
                    sta_data *datahead=NULL;
                    int station_num=readregfile(recv_path,recv_entry->d_name,format_fp,&datahead);
                    printf("%d-%02d-%02d %02d:%02d:%02d %s %d\n", \
                    tm_file->tm_year+1900,tm_file->tm_mon+1,tm_file->tm_mday,tm_file->tm_hour,tm_file->tm_min,tm_file->tm_sec,recv_entry->d_name,station_num);
 
                    /*对站级的数据进行质量控制
                    对于质量不合格的写入日志记录*/
                    if(datahead->next!=NULL)
                     {
                       qc_list(datahead,qc_fp);
                       //对质量合格的台站数据写入到发送目录
               
                       //1.定义文件名
                       char sendfile[1024];
                       sprintf(sendfile,"%s/%s",send_path,recv_entry->d_name);
                       FILE *file_fp;
                       if((file_fp=fopen(sendfile, "w+"))==NULL)
                        {
                          printf("open file err\n");
                          return(0);
                        }
               
                       //2.将sta_data数据结构的first、second、three、four写入到质控后文件
                       sta_data *p=datahead;
                       p=p->next;
                       while(p!=NULL)
                        {
                          fprintf(file_fp,"%s\n%s\n%s\n",p->first,p->second,p->three);
                          if(p->four[0] != 'N')//写入能见度等少数站才有的观测数据
                             fprintf(file_fp,"%s\n",p->four);
                          p=p->next;
                        }
                       fprintf(file_fp,"NNNN");
                       fclose(file_fp);
                     }
                
                    //释放内存
                    sta_data *pointer;
                    while(datahead!=NULL)
                    {
                      pointer = datahead;
                      datahead = datahead->next;
                      free(pointer);
                      pointer=NULL;
                    }
                 
                    //删除这个文件
                    if(remove(recv_filename)==-1)
                    {
                      printf("delete file err:%s\n",recv_filename);
                      return 0;
                    }
                 }
                 else
                 {
                    //删除这个文件
                    if(remove(recv_filename)==-1)
                    {
                      printf("delete file err:%s\n",recv_filename);
                      return 0;
                    }
                 }
             }
            else if(S_ISDIR(statbuf.st_mode))
             {
                if( \
                    (0==strcmp("..", recv_entry->d_name)) || \
                    (0 == strcmp(".",recv_entry->d_name)) || \
                    (0 == strcmp(".prcsnd",recv_entry->d_name)) \
                  )
                {
                   continue;
                }
                
                //删除这个目录
                int rmdir_flag=remove_dir(recv_filename);
             }
            else
             {
                printf("unknow file type,%s\n",recv_filename);
                return 0;            
             }
         }
        closedir(recv_dp);
       
        fclose(format_fp);
        fclose(qc_fp);
        sleep(1);
    }
    return 0;
}
