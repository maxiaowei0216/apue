#include "apue.h"
#include <fcntl.h>

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {	/* child */
        printf("---------- Before ----------\n");
        printf("pid=%d, group=%d\n",getpid(), getpgrp());
        // 打开终端
        if( open("/dev/tty", O_RDONLY) == -1 )
            err_sys("open error");
        // 使用ps指令，查看TTY列，建立会话前为pts/0
        // system("ps");

        // 建立新的会话
        pid = setsid();
        printf("---------- After  ----------\n");
        printf("pid=%d, group=%d\n",getpid(), getpgrp());

        if(getpid() == getpgrp())
            printf("Child is a process group leader.\n");
        else
            printf("Child is NOT　a process group leader.\n");
        // 打开终端
        if( open("/dev/tty", O_RDONLY) == -1 )
            err_sys("open error");
        // 建立会话后，TTY列为?，不能控制终端
        // system("ps");
    }

    exit(0);
}