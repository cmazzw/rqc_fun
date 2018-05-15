#include "rqc.h"
#include "readregfile.h"
#include "qc_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

int main()
{
    //定义收集目录
    char *recv_path="/home/acenter/src/rqc/reg";
    printf("收集区域站数据目录为:%s\n",recv_path);
    
    //定义质控后的发送目录
    char *send_path="/home/acenter/src/rqc/send";
    printf("质控后发送到指定目录:%s\n",send_path);
    
    //定义区域站文件名模版
    char awscard[]="Z_SURF_C_B\?\?\?-REG_*_O_AWS_FTM.txt";
    
    //记录格式检查错误日志
    char *formatlogpath="/home/acenter/src/rqc/log/format.log";
    printf("记录格式检查错误日志:%s\n",formatlogpath);
    FILE *format_fp;
    if((format_fp=fopen(formatlogpath,"w+"))==NULL)
      {
         printf("open format_log faild \n");
         return 0;
      }
    
    //记录质量控制错误日志
    char *qclogpath="/home/acenter/src/rqc/log/qc.log";
    printf("记录质量控制日志:%s\n",qclogpath);
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
         if(match(recv_entry->d_name,awscard))
             {
                /*解析这个文件到站级数据结构,
                将解析的格式错误台站信息保存到日志文件*/
                sta_data *datahead=NULL;
                int station_num=readregfile(recv_path,recv_entry->d_name,format_fp,&datahead);
                printf("%s:%d\n",recv_entry->d_name,station_num);
 
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
               
                    //将sta_data数据结构的first、second、three、four写入到质控后文件
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
             }
      }
    fclose(format_fp);
    fclose(qc_fp);
    closedir(recv_dp);
    return 0;
}
