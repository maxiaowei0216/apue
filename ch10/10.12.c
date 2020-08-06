/**
 * 写结束才看到信号，时间>1s
 **/

#include "apue.h"

static void sig_a(int no)
{
    printf("SIGALRM\n");
}

int main()
{

    char *str;
    FILE *fp;
    size_t size;

    signal(SIGALRM, sig_a);

    if((fp = fopen("/home/mxw/work/apue/ch10/a.txt", "wb+")) == NULL)
        err_sys("fopen error");
    // setvbuf(fp, buf, _IOFBF, 1024*1024*1024);

    alarm(1);

    str = (char *)malloc(1024*1024*1024*sizeof(char));
    if(str == NULL)
        err_sys("malloc error");
    memset(str, '0', 1024*1024*1024*sizeof(char));

    printf("start to fwrite\n");
    size = fwrite(str, sizeof(char), 1024*1024*1024, fp);
    printf("write size:%d\n", (int)size);

    exit(0);
}