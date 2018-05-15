#include <rqc.h>
#include <until.h>
#include <qc_node.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


sta_data *qc_list(sta_data *pHead,FILE *qc_fp)
{
    //记录当前时间
    time_t timer;//time_t就是long int 类型
    struct tm  *tm_struct;//存储时间的结构体
    timer = time(NULL);
    tm_struct = localtime(&timer);//获取了时间结构体
    char qc_time[20];
    sprintf(qc_time,"%d-%02d-%02d %02d:%02d:%02d", \
    tm_struct->tm_year+1900,tm_struct->tm_mon+1,tm_struct->tm_mday,tm_struct->tm_hour,tm_struct->tm_min,tm_struct->tm_sec);

    sta_data *pMove;
    sta_data *pMovePre;
    pMovePre = pHead;
    pMove = pHead->next;
    while (pMove != NULL)
     {
        //测试输出pMove
        struct qc_result result;
        int status=qc_node(pMove,&result);

        //对pMove节点进行质量检查
        if(status==0)//绿色节点
          {
             //此节点不删除，pMovePre和pMove均进行移位操作，对下一个节点进行质控
             //printf("质控结果staion:%s,time:%s,ele:%s,value:%f,filename:%s\n",result.station_num,result.o_time,result.ele,result.ele_value,result.filename);
             pMovePre = pMovePre->next;
             pMove = pMove->next;
          }
        else if(status==1)//黄色节点
          {
             //此节点不删除，pMovePre和pMove均进行移位操作
             pMovePre = pMovePre->next;
             pMove = pMove->next;

             //对黄色节点进行持久化操作,日志?消息队列？
             printf("warn %s %s %s\n",result.station_num,result.o_time,result.filename);
             fprintf(qc_fp,"%s warn %s %s %s %.2f %s\n",qc_time,result.station_num,result.o_time,result.ele,result.ele_value,result.filename);
          }
        else if(status==-1)//红色节点
          {
             //此节点删除
             pMovePre->next = pMove->next;
             free(pMove);
             pMove = pMovePre->next;

             //对红色节点进行持久化操作,日志?消息队列？
             printf("err %s %s %s\n",result.station_num,result.o_time,result.filename);
             fprintf(qc_fp,"%s err %s %s %s %.2f %s\n",qc_time,result.station_num,result.o_time,result.ele,result.ele_value,result.filename);
          }
    }
    return pHead;
}

