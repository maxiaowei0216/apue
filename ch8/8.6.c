#include "apue.h"

int main()
{
    pid_t pid;

    if( (pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid == 0)  /* child */
        exit(0);

    // 父进程不处理子进程，即为僵死进程
    printf("child pid = %d\n", pid);
    sleep(2);
    system("ps -o pid,ppid,state");
    exit(0);
}