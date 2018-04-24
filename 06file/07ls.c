#include <unistd.h> //UNIX标准头文件
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <dirent.h>

#define ERR_EXIT(m)\
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main(int argc, char *argv[])
{
    char dirName[1024] = ".";
    if(argc > 1)
        strcpy(dirName, argv[1]);

    DIR *dir = opendir(dirName);
    struct dirent *de;
    while((de = readdir(dir)) != NULL)
    {
        printf("%s\n", de->d_name);
    }
    
    closedir(dir);
    return 0;
}

