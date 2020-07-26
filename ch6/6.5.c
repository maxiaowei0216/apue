#include "apue.h"
#include <time.h>

int main(void)
{
    time_t now;
    struct tm *tmp;
    char buf[64];

    // 获取当前时间
    time(&now);
    // 分解时间
    tmp = localtime(&now);
    // 格式化输出 xxxx年 xx月 xx日 星期x xx:xx:xx CST
    if(strftime(buf, 64, "%Y年 %m月 %d日 %A %T %Z\n", tmp) == 0) {
        printf("buffer too small\n");
    }
    else {
        printf("%s", buf);
    }

    exit(0);
}