#ifndef _RQC_H_
#define _RQC_H_

#define LEN_DATA sizeof(sta_data)
#define LEN_THRESH sizeof(threshold)

struct qc_result
{
    char station_num[6];
    char o_time[15];
    char ele[16];
    double ele_value;
    char filename[64];
};

typedef struct qc_threshold
{
   char mon[3];
   double wind_min;
   double wind_max;
   double rain_min;
   double rain_max;
   double temp_min;
   double temp_max;
   double pres_min;
   double pres_max;
   double g_temp_min;
   double g_temp_max;
   double s_pres_min;
   double s_pres_max;
}threshold;

struct station_temp
{
    char station_num[6];//台站号   H0414
    char o_time[15];//观测时间     20180417000000
    char wind2[4];//两分钟平均风速  112
    char wind10[4];//十分钟平均风速 105
    char wind_max[4];//最大风速     109
    char wind_s[4];
    char wind_j[4];
    char rain[5];//小时降水量0000
    char tem[5];//气温0140
    char tem_max[5];//最高气温0140
    char tem_min[5];//最低气温0130
    char pres[6];//本站气压   /////
    char pres_max[6];         /////
    char pres_min[6];
    char g_temp[5];
    char g_temp_max[5];
    char g_temp_min[5];
    char s_pres[6];//海平面气压
    char first[35];
    char second[263];
    char three[122];
    char four[136];
    char filename[64];
};

typedef struct station_data
{
   char station_num[6];//台站号   H0414
   char o_time[15];//观测时间     20180417000000
   double wind2;//两分钟平均风速  112
   double wind10;//十分钟平均风速 105
   double wind_max;//最大风速     109
   double wind_s;
   double wind_j;
   double rain;//小时降水量0000
   double tem;//气温0140
   double tem_max;//最高气温0140
   double tem_min;//最低气温0130
   double pres;//本站气压   /////
   double pres_max;         /////
   double pres_min;
   double g_temp;
   double g_temp_max;
   double g_temp_min;
   double s_pres;//海平面气压
   char first[35];
   char second[263];
   char three[122];
   char four[136];
   char filename[64];//数据所在文件名------这里注意，赋值越界了。
   struct station_data *next;
}sta_data;

#endif

