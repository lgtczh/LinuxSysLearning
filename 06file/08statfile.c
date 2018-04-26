#include <unistd.h> //UNIX标准头文件
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define ERR_EXIT(m)\
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

// 将dev_t强制转为无符号短整型后右移8位,最后转为int,得到主设备号
#define MAJOR(st_dev) (int)((unsigned short)st_dev>>8)
//将dev_t强制转为unsigned short后，和0xFF相与，最后强制转换为int，得到次设备号
#define MINOR(st_dev) (int)((unsigned short)st_dev & 0xFF)

char filetype(struct stat*);
void printFileType(char, struct stat*);
void filePerm(char, struct stat*, char*);

int main(int argc, char *argv[])
{
    if (argc != 2){
        fprintf(stderr, "Usage %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    fprintf(stdout, "Filename : %s\n", argv[1]);    
    
    struct stat sbuf;
    if (lstat(argv[1], &sbuf) == -1){
        ERR_EXIT("stat error");
    }
    
    printf("File number: major %d, minor %d\n", MAJOR(sbuf.st_dev), MINOR(sbuf.st_dev));
    printf("File inode: %d\n", (int)sbuf.st_ino);
    
    char type = filetype(&sbuf);
    printFileType(type, &sbuf);
    char perm[] = "----------";
    filePerm(type, &sbuf, perm);
    printf("File permission: %s\n", perm);
    
    return 0;
}

char filetype(struct stat *buf)
{
    mode_t mode = buf->st_mode;
    switch(mode & S_IFMT)
    {
        case S_IFSOCK:
            return 's';
        case S_IFLNK:
            return 'l';
        case S_IFREG:
            return '-';
        case S_IFBLK:
            return 'b'; 
        case S_IFDIR:
            return 'd';
        case S_IFCHR:
            return 'c';
        case S_IFIFO:
            return 'p';
        default:
            return '?';
    }
}

void printFileType(char type, struct stat *buf)
{
    
    printf("Filetype:");
    switch(type)
    {
        case 's':
            printf("socket\n");
            break;
        case 'l':
            printf("symbolic link\n");
            break;
        case '-':
            printf("regular file\n");
            break;
        case 'b': 
            printf("block device\n");
            break;
        case 'd':
            printf("directory\n");
            break;
        case 'c':
            printf("character device\n");
            break;
        case 'p':
            printf("FIFO\n");
            break;
        default:
            printf("unknown file type\n");
    }
    if (type == 'b' || type == 'c'){
        printf("Device number:major %d, minor %d\n", MAJOR(buf->st_rdev), MINOR(buf->st_rdev));
    }
}
void filePerm(char type, struct stat *buf, char *perm)
{
    perm[0] = type;
    mode_t pm =  buf->st_mode & 07777;
    
    if ((pm & S_IRWXU) == S_IRWXU){
        perm[1] = 'r';
        perm[2] = 'w';
        perm[3] = 'x';
    }else{
        if (pm & S_IRUSR)
            perm[1] = 'r';
        if (pm & S_IWUSR)
            perm[2] = 'w';
        if (pm & S_IXUSR)
            perm[3] = 'x';
    }
     
    if ((pm & S_IRWXG) == S_IRWXG){
        perm[4] = 'r';
        perm[5] = 'w';
        perm[6] = 'x';
    }else{
        if (pm & S_IRGRP)
            perm[4] = 'r';
        if (pm & S_IWGRP)
            perm[5] = 'w';
        if (pm & S_IXGRP)
            perm[6] = 'x';
    }

    if ((pm & S_IRWXO) == S_IRWXO){
        perm[7] = 'r';
        perm[8] = 'w';
        perm[9] = 'x';
    }else{
        if (pm & S_IROTH)
            perm[7] = 'r';
        if (pm & S_IWOTH)
            perm[8] = 'w';
        if (pm & S_IXOTH)
            perm[9] = 'x';
    }
    perm[10] = '\0';
}   
