#include <sqlite3.h>
#include <rqc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getthresholdbymon(threshold **th,const char *mon)
{
  *th=(threshold*)malloc(LEN_THRESH);

  sqlite3 *db=NULL;
  int rc;
  //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件  
  rc = sqlite3_open("/home/acenter/src/rqc/threshDB.db", &db);
  if(rc)
  {
    printf("Can't open database: %s/n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 0;
  }
  char sql[256];
  sprintf(sql,"select * FROM qc WHERE MON='%s'",mon);
  char **data;
  char *errmsg=NULL;
  int nRow, nColumn;
  int ret = sqlite3_get_table(db,sql,&data,&nRow,&nColumn,&errmsg);
  int i,j,index;
  if(ret == SQLITE_OK)
    {
       //输出数据
       index=nColumn;
       for(i=0;i<nRow;i++)
        {
          for(j=0;j<nColumn;j++)
            {
               //printf("%s\n",data[index]);
               if(index==nColumn)
                  strcpy((*th)->mon,data[index]);
               if(index==(nColumn+1))
                  (*th)->wind_min=atof(data[index])/10;
               if(index==(nColumn+2))
                  (*th)->wind_max=atof(data[index])/10;
               if(index==(nColumn+3))
                  (*th)->rain_min=atof(data[index])/10;
               if(index==(nColumn+4))
                  (*th)->rain_max=atof(data[index])/10;                 
               if(index==(nColumn+5))
                {
                  char temp_min[4],zf_flag_min[2];
                  substr(temp_min,data[index],1,3);
                  substr(zf_flag_min,data[index],0,1);
                  if(zf_flag_min[0]=='0')
                    (*th)->temp_min=atof(temp_min)/10;
                  else
                    (*th)->temp_min=atof(temp_min)/10*(-1);
                }
               if(index==(nColumn+6))
                {
                  char temp_max[4],zf_flag_max[2];
                  substr(temp_max,data[index],1,3);
                  substr(zf_flag_max,data[index],0,1);
                  if(zf_flag_max[0]=='0')
                    (*th)->temp_max=atof(temp_max)/10;
                  else
                    (*th)->temp_max=atof(temp_max)/10*(-1);
                }
               if(index==(nColumn+7))
                  (*th)->pres_min=atof(data[index])/10;
               if(index==(nColumn+8))
                  (*th)->pres_max=atof(data[index])/10;
               if(index==(nColumn+9))
                {
                  char g_temp_min[4],g_zf_flag_min[2];
                  substr(g_temp_min,data[index],1,3);
                  substr(g_zf_flag_min,data[index],0,1);
                  if(g_zf_flag_min[0]=='0')
                    (*th)->g_temp_min=atof(g_temp_min)/10;
                  else
                    (*th)->g_temp_min=atof(g_temp_min)/10*(-1);
                }
               if(index==(nColumn+10))
                {
                  char g_temp_max[4],g_zf_flag_max[2];
                  substr(g_temp_max,data[index],1,3);
                  substr(g_zf_flag_max,data[index],0,1);
                  if(g_zf_flag_max[0]=='0')
                    (*th)->g_temp_max=atof(g_temp_max)/10;
                  else
                    (*th)->g_temp_max=atof(g_temp_max)/10*(-1);
                } 
               if(index==(nColumn+11))
                  (*th)->s_pres_min=atof(data[index])/10;
               if(index==(nColumn+12))
                  (*th)->s_pres_max=atof(data[index])/10;
               index++;
            }
        }
    }
  sqlite3_free_table(data);
  sqlite3_close(db); //关闭数据库*/
  return 1;
}

