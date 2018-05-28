#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

int setup_daemon(int nochdir, int noclose);

int main(int argc, char *argv[])
{
    printf("I am daemon\n");
    printf("%d\n", setup_daemon(0, 0));
    printf("I am daemon\n");
    for(;;);
    return 0;
}

int setup_daemon(int nochdir, int noclose)
{
    pid_t pid;
    
    if ((pid =fork()) < 0)
        ERR_EXIT("fork");
    else if (pid >  0)
        exit(EXIT_SUCCESS);  // 父进程退出

    // 执行到这里的一定是子进程
    setsid();  // 创建新的会话期
    if (nochdir == 0)
        chdir("/"); // 运行目录改成根目录
    // 关闭标准I/O
    if (noclose == 0){
        int i;
        for (i = 0;i < 3; ++ i)
            close(i);
        // 然后打开/dev/null，open返回0从而标准输入重定向到/dev/null 
        open("/dev/null", O_RDWR);
        dup(0);  // 复制文件描述符0，将标准输出重定向到/dev/null
        dup(0);  // 将标准错误重定向到/dev/null
    }

    return 0;
}

