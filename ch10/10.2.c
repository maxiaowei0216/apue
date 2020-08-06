#include "apue.h"
#include <signal.h>

#define SIG2STR_MAX 64
#define SIG_MAX     64

#if 0
int sig2str(int signo, char *str)
{
    strcpy(str, strsignal(signo));

    return 0;
}
#else
// 暂时只定义了6个，其余的添加即可
char *sig_str[SIG_MAX] = {"HUP","INT","QUIT","ILL","TRAP","ABRT"};

int sig2str(int signo, char *str)
{
    // 参数检查
    if((signo < 1) || (signo > SIG_MAX) || (str == NULL))
        return -1;

    // 仅定义了6个，所以要限定范围
    if(signo <= 6)
        strcpy(str, sig_str[signo-1]);
    else
        strcpy(str, "NO DEFINE");

    return 0;
}
#endif

int main()
{
    char buf[SIG2STR_MAX];
    int signo = 0;
    scanf("%d", &signo);

    while(signo != -1) {
        if(sig2str(signo, buf) < 0)
            err_sys("sig2str error");
        else
            printf("%s\n", buf);

        scanf("%d", &signo);
    }

    exit(0);
}