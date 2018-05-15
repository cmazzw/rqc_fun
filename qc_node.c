#include <rqc.h>
#include <getthresholdbymon.h>
#include <until.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//返回值为-1表示红色，返回值为0表示绿色，返回值为1表示黄色
int qc_node(sta_data *pNode,struct qc_result *result)
{
   //定义阈值数据结构
   threshold *th;
   
   //获取观测数据的观测时间
   char mon[3];
   substr(mon,pNode->o_time,4,2);//月份

   //根据月份mon获取阈值数据th
   getthresholdbymon(&th,mon);
   
   //以下根据阈值和观测值进行单节点质量控制
   //1.对两米风速进行质控  红色
   if((pNode->wind2 > th->wind_max || pNode->wind2 < th->wind_min) && pNode->wind2 !=999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"wind2",15);result->ele[15]='\0';
      result->ele_value=pNode->wind2;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   else
   {
      //printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
     // printf("两分钟风速最小值%f < 观测值%f < 两分钟风速最大值%f\n",th->wind_min,pNode->wind2,th->wind_max);
   }
   
   //2.对十米风速进行质控   红色
   if((pNode->wind10 > th->wind_max || pNode->wind10 < th->wind_min) && pNode->wind10!=999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"wind10",15);result->ele[15]='\0';
      result->ele_value=pNode->wind10;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   else
   {
      //printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
      //printf("十分钟风速最小值%f < 观测值%f < 十分钟风速最大值%f\n",th->wind_min,pNode->wind10,th->wind_max);
   }
   
   //3.对最大风速进行质控   红色
   if((pNode->wind_max > th->wind_max || pNode->wind_max < th->wind_min) && pNode->wind_max!=999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"wind_max",15);result->ele[15]='\0';
      result->ele_value=pNode->wind_max;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   else
   {
      //printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
      //printf("最大分钟风速最小值%f < 观测值%f < 最大风速最大值%f\n",th->wind_min,pNode->wind_max,th->wind_max);
   }
   
   //4.对瞬时风速进行质控   红色
   if((pNode->wind_s > th->wind_max || pNode->wind_s < th->wind_min) && pNode->wind_s != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"wind_s",15);result->ele[15]='\0';
      result->ele_value=pNode->wind_s;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   else
   {
      //printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
      //printf("瞬时风速最小值%f < 观测值%f < 瞬时风速最大值%f\n",th->wind_min,pNode->wind2,th->wind_max);
   }
 
   //5.对极大风速进行质控   红色
   if((pNode->wind_j > th->wind_max || pNode->wind_j < th->wind_min) && pNode->wind_j != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"wind_j",15);result->ele[15]='\0';
      result->ele_value=pNode->wind_j;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   else
   {
      //printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
      //printf("极大风速最小值%f < 观测值%f < 极大风速最大值%f\n",th->wind_min,pNode->wind2,th->wind_max);
   }
 
   //6.对小时降水量进行质控  黄色
   if((pNode->rain > th->rain_max || pNode->rain < th->rain_min) && pNode->rain != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"rain",15);result->ele[15]='\0';
      result->ele_value=pNode->rain;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(1);
   }
   else
   {
     // printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
      // printf("降水量最小值%f < 观测值%f < 降水量最大值%f\n",th->rain_min,pNode->rain,th->rain_max);
   }
   
   //7.对气温/温度进行质控   红色
   if((pNode->tem > th->temp_max || pNode->tem < th->temp_min) && pNode->tem != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"tem",15);result->ele[15]='\0';
      result->ele_value=pNode->tem;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   else
   {
      //printf("对%s站的%s时次的资料进行质控：\n",pNode->station_num,pNode->o_time);
       //printf("气温最小值%f < 观测值%f < 气温最大值%f\n",th->temp_min,pNode->tem,th->temp_max);
   }
 
   //8.对最高温度进行质控   红色
   if((pNode->tem_max > th->temp_max || pNode->tem_max < th->temp_min) && pNode->tem_max != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"tem_max",15);result->ele[15]='\0';
      result->ele_value=pNode->tem_max;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }

   //9.对最低温度进行质控   红色
   if((pNode->tem_min > th->temp_max || pNode->tem_min < th->temp_min) && pNode->tem_min != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"tem_min",15);result->ele[15]='\0';
      result->ele_value=pNode->tem_min;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }

   //10.对本站气压进行质控   红色
   if((pNode->pres > th->pres_max || pNode->pres < th->pres_min) && pNode->pres != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"pres",15);result->ele[15]='\0';
      result->ele_value=pNode->pres;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }

   //11.对本站最大气压进行质控   红色
   if((pNode->pres_max > th->pres_max || pNode->pres_max < th->pres_min) && pNode->pres_max != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"pres_max",15);result->ele[15]='\0';
      result->ele_value=pNode->pres_max;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   
   //12.对本站最小气压进行质控   红色
   if((pNode->pres_min > th->pres_max || pNode->pres_min < th->pres_min) && pNode->pres_min != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"pres_min",15);result->ele[15]='\0';
      result->ele_value=pNode->pres_min;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   
   //13.对地温进行质控   红色
   if((pNode->g_temp > th->g_temp_max || pNode->g_temp < th->g_temp_min) && pNode->g_temp != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"g_temp",15);result->ele[15]='\0';
      result->ele_value=pNode->g_temp;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   
   //13.对最高地温进行质控   红色
   if((pNode->g_temp_max > th->g_temp_max || pNode->g_temp_max < th->g_temp_min) && pNode->g_temp_max != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"g_temp_max",15);result->ele[15]='\0';
      result->ele_value=pNode->g_temp_max;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   
   //14.对最低地温进行质控   红色
   if((pNode->g_temp_min > th->g_temp_max || pNode->g_temp_min < th->g_temp_min) && pNode->g_temp_min != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"g_temp_min",15);result->ele[15]='\0';
      result->ele_value=pNode->g_temp_min;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   
   //15.对海平面气压进行质控   红色
   if((pNode->s_pres > th->s_pres_max || pNode->s_pres < th->s_pres_min) && pNode->s_pres != 999.999)//质控不过
   {
      strncpy(result->station_num,pNode->station_num,5);result->station_num[5]='\0';
      strncpy(result->o_time,pNode->o_time,14);result->o_time[14]='\0';
      strncpy(result->ele,"s_pres",15);result->ele[15]='\0';
      result->ele_value=pNode->s_pres;
      strncpy(result->filename,pNode->filename,63);result->filename[63]='\0';
      return(-1);
   }
   
   free(th);
   return(0);
}

