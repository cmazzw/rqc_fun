#include <rqc.h>
#include <until.h>
#include <stdio.h>
#include <stdlib.h>

//对于缺测"////"则转换为特征值999.999
int strtodouble(sta_data *pTail,struct station_temp *sta_temp)
{
    sprintf(pTail->station_num,sta_temp->station_num);
    sprintf(pTail->o_time,sta_temp->o_time);

    //两分钟风速
    if(sta_temp->wind2[0]=='/')
        pTail->wind2=999.999;
    else
        pTail->wind2=atof(sta_temp->wind2)/10;

    //十分钟风速
    if(sta_temp->wind10[0]=='/')
        pTail->wind10=999.999;
    else
        pTail->wind10=atof(sta_temp->wind10)/10;

    //最大风速
    if(sta_temp->wind_max[0]=='/')
        pTail->wind_max=999.999;
    else
        pTail->wind_max=atof(sta_temp->wind_max)/10;

    //瞬时风速
    if(sta_temp->wind_s[0]=='/')
        pTail->wind_s=999.999;
    else
        pTail->wind_s=atof(sta_temp->wind_s)/10;

    //极大风速
    if(sta_temp->wind_j[0]=='/')
        pTail->wind_j=999.999;
    else
        pTail->wind_j=atof(sta_temp->wind_j)/10;

    //降雨量数据
    if(sta_temp->rain[0]=='/')
        pTail->rain=999.999;
    else
        pTail->rain=atof(sta_temp->rain)/10;

    //温度
    if(sta_temp->tem[0]=='/')
        pTail->tem=999.999;
    else
      {
         char temp[4],zf_flag[2];
         substr(temp,sta_temp->tem,1,3);
         substr(zf_flag,sta_temp->tem,0,1);
         if(zf_flag[0]=='0')
            pTail->tem=atof(temp)/10;
         else
            pTail->tem=atof(temp)/10*(-1);
      }

    //最大温度
    if(sta_temp->tem_max[0]=='/')
       pTail->tem_max=999.999;
    else
      {
         char temp_max[4],zf_flag_max[2];
         substr(temp_max,sta_temp->tem_max,1,3);
         substr(zf_flag_max,sta_temp->tem_max,0,1);
         if(zf_flag_max[0]=='0')
            pTail->tem_max=atof(temp_max)/10;
         else
            pTail->tem_max=atof(temp_max)/10*(-1);
      }

    //最低温度
    if(sta_temp->tem_min[0]=='/')
       pTail->tem_min=999.999;
    else
      {
         char temp_min[4],zf_flag_min[2];
         substr(temp_min,sta_temp->tem_min,1,3);
         substr(zf_flag_min,sta_temp->tem_min,0,1);
         if(zf_flag_min[0]=='0')
            pTail->tem_min=atof(temp_min)/10;
         else
            pTail->tem_min=atof(temp_min)/10*(-1);
      }

    //本站气压
    if(sta_temp->pres[0]=='/')
       pTail->pres=999.999;
    else
       pTail->pres=atof(sta_temp->pres)/10;

    //最低气压
    if(sta_temp->pres_min[0]=='/')
       pTail->pres_min=999.999;
    else
       pTail->pres_min=atof(sta_temp->pres_min)/10;

    //最高气压
    if(sta_temp->pres_max[0]=='/')
       pTail->pres_max=999.999;
    else
       pTail->pres_max=atof(sta_temp->pres_max)/10;

    //草面温度
    if(sta_temp->g_temp[0]=='/')
       pTail->g_temp=999.999;
    else
     {
       char g_temp_t[4],g_temp_flag[2];
       substr(g_temp_t,sta_temp->g_temp,1,3);
       substr(g_temp_flag,sta_temp->g_temp,0,1);
       if(g_temp_flag[0]=='0')
          pTail->g_temp=atof(g_temp_t)/10;
       else
          pTail->g_temp=atof(g_temp_t)/10*(-1);
     }

    //最高草面温度
    if(sta_temp->g_temp_max[0]=='/')
       pTail->g_temp_max=999.999;
    else
     {
       char g_temp_max_t[4],g_temp_max_flag[2];
       substr(g_temp_max_t,sta_temp->g_temp_max,1,3);
       substr(g_temp_max_flag,sta_temp->g_temp_max,0,1);
       if(g_temp_max_flag[0]=='0')
          pTail->g_temp_max=atof(g_temp_max_t)/10;
       else
          pTail->g_temp_max=atof(g_temp_max_t)/10*(-1);
     }

    //最低草面温度
    if(sta_temp->g_temp_min[0]=='/')
       pTail->g_temp_min=999.999;
    else
     {
       char g_temp_min_t[4],g_temp_min_flag[2];
       substr(g_temp_min_t,sta_temp->g_temp_min,1,3);
       substr(g_temp_min_flag,sta_temp->g_temp_min,0,1);
       if(g_temp_min_flag[0]=='0')
         pTail->g_temp_min=atof(g_temp_min_t)/10;
       else
         pTail->g_temp_min=atof(g_temp_min_t)/10*(-1);
     }

    //海平面气压
    if(sta_temp->s_pres[0]=='/')
       pTail->s_pres=999.999;
    else
       pTail->s_pres=atof(sta_temp->s_pres)/10;

    sprintf(pTail->first,sta_temp->first);
    sprintf(pTail->second,sta_temp->second);
    sprintf(pTail->three,sta_temp->three);
    sprintf(pTail->four,sta_temp->four);
    sprintf(pTail->filename,sta_temp->filename);
    return(1); 
}

