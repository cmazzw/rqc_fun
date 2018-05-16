#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

//**只能删除非.和非..和非.prcsnd的目录**//
int remove_dir(const char *dir)
{
    char dir_name[128];
    DIR *dirp;
    struct dirent *dp;
    struct stat dir_stat;

    // 参数传递进来的目录不存在，直接返回
    if ( 0 != access(dir, F_OK) ) {
        return 0;
    }

    // 获取目录属性失败，返回错误
    if ( 0 > stat(dir, &dir_stat) ) {
        perror("get directory stat error");
        return -1;
    }

    // 普通文件直接删除
    if ( S_ISREG(dir_stat.st_mode) ) 
     {
        remove(dir);
     }
    // 目录文件，递归删除目录中内容 
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
            
            // 递归调用
            remove_dir(dir_name);
          }
        closedir(dirp);
        
        // 删除空目录
        rmdir(dir);
     } 
    else 
      {
        perror("unknow file type!");    
      }
    return 0;
}