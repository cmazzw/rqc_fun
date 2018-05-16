#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

//**ֻ��ɾ����.�ͷ�..�ͷ�.prcsnd��Ŀ¼**//
int remove_dir(const char *dir)
{
    char dir_name[128];
    DIR *dirp;
    struct dirent *dp;
    struct stat dir_stat;

    // �������ݽ�����Ŀ¼�����ڣ�ֱ�ӷ���
    if ( 0 != access(dir, F_OK) ) {
        return 0;
    }

    // ��ȡĿ¼����ʧ�ܣ����ش���
    if ( 0 > stat(dir, &dir_stat) ) {
        perror("get directory stat error");
        return -1;
    }

    // ��ͨ�ļ�ֱ��ɾ��
    if ( S_ISREG(dir_stat.st_mode) ) 
     {
        remove(dir);
     }
    // Ŀ¼�ļ����ݹ�ɾ��Ŀ¼������ 
    else if ( S_ISDIR(dir_stat.st_mode) ) 
     {
        //printf("i am fun dir is %s\n",dir);
        dirp = opendir(dir);
        while ( (dp=readdir(dirp)) != NULL ) 
          {
            if ( (0 == strcmp(".", dp->d_name)) || (0 == strcmp("..", dp->d_name)) ) 
              {
                 continue;
              }
            sprintf(dir_name, "%s/%s", dir, dp->d_name);
            
            // �ݹ����
            remove_dir(dir_name);
          }
        closedir(dirp);
        
        // ɾ����Ŀ¼
        rmdir(dir);
     } 
    else 
      {
        perror("unknow file type!");    
      }
    return 0;
}