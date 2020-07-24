#include "apue.h"
#include <fcntl.h>

char buf1[] = "1234567890";
char buf2[] = "0987654321";

int main(void)
{
    int fd,fd2;
    char rd;

    // 创建文件file.hole
    if((fd = creat("file.hole", FILE_MODE)) < 0) {
        err_sys("Create error!");
    }
    if( write(fd, buf1, 10) != 10) {
        err_sys("Buf1 write error!");
    }
    // printf("Create file OK\n");
    // 制造空洞
    if( lseek(fd, 100, SEEK_SET) == -1) {
        err_sys("Lseek error!");
    }
    if( write(fd, buf2, 10) != 10) {
        err_sys("Buf2 write error!");
    }
    close(fd);
    // printf("Create hole OK\n");

    // 复制到in.hole
    if( (fd = open("file.hole", O_RDONLY)) < 0) {
        err_sys("Open error!");
    }
    if((fd2 = creat("in.hole", FILE_MODE)) < 0) {
        err_sys("Create error!");
    }
    while(read(fd, &rd, 1)){
        if(rd == '\0'){ //空洞字符
            continue;
        }
        if(write(fd2, &rd, 1) != 1) {
            err_sys("Write error");
        }
    }

    exit(0);
}