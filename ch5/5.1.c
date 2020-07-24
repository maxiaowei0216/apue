#include "apue.h"

void my_setbuf(FILE *restrict fp, char *restrict buf)
{
    // 无缓冲区
    if(buf == NULL || fp == stderr){
        if (setvbuf(fp, buf, _IONBF, 1) != 0)
            err_sys("setvbuf failed");
    }
    else {
        // 行缓冲
        if(fp == stdin || fp == stdout) {
            if (setvbuf(fp, buf, _IOLBF, BUFSIZ) != 0)
                err_sys("setvbuf failed");
        }
        else {
            // 全缓冲
            if (setvbuf(fp, buf, _IOFBF, BUFSIZ) != 0)
                err_sys("setvbuf failed");
        }
    }
}

int main(void)
{

    exit(0);
}