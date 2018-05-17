#include <rqc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//对于缺测"////"则记录特征值999.999
int readregfile(char *path,char *filename,FILE *log_fp,sta_data **pHead)
{
    //记录当前时间
    time_t timer;//time_t就是long int 类型
    struct tm  *tm_struct;//存储时间的结构体
    timer = time(NULL);
    tm_struct = localtime(&timer);//获取了时间结构体
    char format_time[20];
    sprintf(format_time,"%d-%02d-%02d %02d:%02d:%02d", \
    tm_struct->tm_year+1900,tm_struct->tm_mon+1,tm_struct->tm_mday,tm_struct->tm_hour,tm_struct->tm_min,tm_struct->tm_sec);

    sta_data *p,*pTail;

    *pHead=pTail=(sta_data*)malloc(LEN_DATA);

    char fileallname[512];
    sprintf(fileallname,"%s/%s",path,filename);
    FILE* reg_fp = fopen(fileallname, "r");
    char line[300];
    int num=0;//记录当前读取的num行,前提是每组有四行
    int line_num=0;//记录真实的行数
    int group=0;//记录站数，也就是第几组
    int station_num=0;

    struct station_temp sta_temp;
    
    while (fgets(line, sizeof(line), reg_fp))
      {
         line_num++;
         if(num-group*4==0)//解析第一行(基本信息)
            {
               //printf("解析第一行\n");
               if(reglen(line)==34)
                 {
                    int f_status=sscanf(line,"%5s",sta_temp.station_num);
                    strncpy(sta_temp.first,line,34);sta_temp.first[34]='\0';
                    if(f_status!=1)
                       {
                         //重新对错误数据进行异常值赋值，并提醒错误数据
                         sprintf(sta_temp.station_num,"99999");
                         fprintf(log_fp,"%s %s %d 基本信息字节数正确,格式错误\n",format_time,filename,line_num);
                       }
                 }
               else
                  {
                     sprintf(sta_temp.station_num,"99999");
                     strncpy(sta_temp.first,line,34);sta_temp.first[34]='\0';
                     fprintf(log_fp,"%s %s %d 基本信息行的字节数不正确\n",format_time,filename,line_num);
                  }
               num++;
               continue;
            }
         else if(num-group*4==1)//解析第二行(主要要素)
            {
               if(reglen(line)==262)
                 {
                   int s_status=sscanf(line,"%14s %*s %3s %*s %3s %*s %3s %*s %*s %3s \
                   %*s %3s %*s %4s %4s %4s %*s %4s %*s %*s %*s %*s %*s %*s %5s %5s %*s %5s %*s %4s \
                   %4s %*s %4s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %5s %*s %*s %*s", \
                   sta_temp.o_time,sta_temp.wind2,sta_temp.wind10,sta_temp.wind_max,sta_temp.wind_s,sta_temp.wind_j, \
                   sta_temp.rain,sta_temp.tem,sta_temp.tem_max,sta_temp.tem_min,sta_temp.pres,sta_temp.pres_max,sta_temp.pres_min, \
                   sta_temp.g_temp,sta_temp.g_temp_max,sta_temp.g_temp_min,sta_temp.s_pres);
                   strncpy(sta_temp.second,line,262);sta_temp.second[262]='\0';
                   if(s_status!=17)
                       {
                         //重新对错误数据进行异常值赋值，并提醒错误数据
                         sprintf(sta_temp.o_time,"99999999999999");
                         fprintf(log_fp,"%s %s %d 第二段观测数据字节数正确，格式错误\n",format_time,filename,line_num);
                       }
                 }
               else
                  {
                     //重新对错误数据进行异常值赋值，并提醒错误数据
                     sprintf(sta_temp.o_time,"99999999999999");
                     fprintf(log_fp,"%s %s %d 第二行观测数据的字节数不正确\n",format_time,filename,line_num);
                  }
               num++;
           }
         else if(num-group*4==2)//解析第三行(小时内分钟降水)
            {
               strncpy(sta_temp.three,line,121);sta_temp.three[121]='\0';
               num++;
           }
         else if(num-group*4==3)//解析第四行
            {
               group++;
               if(reglen(line)==34)
                 {
                    //读到了新的台站数据
                    //0、将第四行赋值为NNNN
                    strncpy(sta_temp.four,"NNNN",135);sta_temp.four[135]='\0';
                    strncpy(sta_temp.filename,filename,46);sta_temp.filename[46]='\0';
                    //printf("filename:%s-->struct:%s\n",filename,sta_temp.filename);
                    //1、先将上一个格式正确的台站数据写入
                    if(strcmp(sta_temp.station_num,"99999")!=0 && strcmp(sta_temp.o_time,"99999999999999")!=0)
                      {
                         //格式正确的数据写入
                         station_num++;
                         p=pTail;
                         pTail=(sta_data*)malloc(LEN_DATA);
                         strtodouble(pTail,&sta_temp);//将字符串格式转换为double格式i
                         p->next=pTail;
                      }
                    //2、置空结构体
                    memset(&sta_temp,0,sizeof(struct station_temp));
                    //3、读取新的台站的第一行数据
                    int n_status=sscanf(line,"%5s",sta_temp.station_num);
                    strncpy(sta_temp.first,line,34);sta_temp.first[34]='\0';
                    if(n_status!=1)
                       {
                         //重新对错误数据进行异常值赋值，并提醒错误数据
                         sprintf(sta_temp.station_num,"99999");
                         printf("format.err-[基本信息字节数正确，格式错误]-line:%d-file:%s\n",line_num,filename);
                       }
                    num=num+2;
                 }
               else if(reglen(line)==135||line[0]=='N')//水文站末尾行为NNNN ,由于有空格，所以reglen(line)==5
                 {
                    //读取能见度或者NNNN数据
                    sprintf(sta_temp.four,line);
                    //sprintf(sta_temp.filename,filename);
                    strncpy(sta_temp.filename,filename,46);sta_temp.filename[46]='\0';
                    //将本次台站的数据写入
                    if(strcmp(sta_temp.station_num,"99999")!=0 && strcmp(sta_temp.o_time,"99999999999999")!=0)
                      {
                         //格式正确的数据写入
                         station_num++;
                         p=pTail;
                         pTail=(sta_data*)malloc(LEN_DATA);
                         strtodouble(pTail,&sta_temp);//将字符串格式转换为double格式
                         p->next=pTail;
                      }
                    //2、置空结构体
                    memset(&sta_temp,0,sizeof(struct station_temp));
                    num++;
                 }
               else
                 {
                    fprintf(log_fp,"%s %s %d 这个站的数据格式错误，以下数据不再读取\n",format_time,filename,line_num);
                    pTail->next=NULL;
                    return(group);
                 }
           }
      }
    fclose(reg_fp);
    pTail->next=NULL;
    return(station_num);
}

