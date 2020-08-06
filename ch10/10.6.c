/**
 * 编译时注意使用作者编写好的signal.c文件
 * 自带的signal函数可能有问题，会导致无法二次捕获信号
 * https://blog.csdn.net/cinmyheart/article/details/22655659
 **/
#include "apue.h"
#include <fcntl.h>

// 数字位数
#define NUMBER_SIZE (5)

static int pr_number(int fd, int is_parent)
{
    char buf[NUMBER_SIZE+1];
    int i, div, number = 0;
    ssize_t size;

    // 到达文件开头
    if(lseek(fd, 0, SEEK_SET) < 0) {
        err_sys("lseek error");
    }
    // 读数据
    if((size = read(fd, buf, NUMBER_SIZE)) < 0) {
        err_sys("read error");
    }

    // 转换为数字
    for(i = 0; i<size; i++) {
        // 应该检查buf[i]是否为数字，此处省略
        number = number * 10 + (buf[i] - '0');
    }
    number++;
    // 数字增长到50就停止
    if(number > 50) {
        printf("number too big\n");
        return -1;
    }
    else {
        printf("number=%d,", number);
    }

    // 将数字写入数组
    memset(buf, 0, sizeof(buf));
    div = 1;
    for(i = NUMBER_SIZE-1; i>0; i--)
        div *= 10;
    // 找到最高位
    while(((number/div) == 0) && (div > 0)) {
        div /= 10;
    }
    for(i = 0; div > 0; i++) {
        buf[i] = number / div + '0';
        number %= div;
        div /= 10;
    }
    buf[i] = '\0';

    // 写入文件
    if(lseek(fd, 0, SEEK_SET) < 0) {
        err_sys("lseek error");
    }
    if(write(fd, buf, i) < 0) {
        err_sys("write error");
    }
    
    if(is_parent) {
        printf("writed by parent\n");
    }
    else {
        printf("writed by child\n");
    }
    return 0;
}

int main()
{
    int fd,is_continue=1;
    pid_t pid;
    char c[1] = {'0'};

    // create file
    if((fd = creat("a.txt", FILE_MODE)) < 0) {
        err_sys("create error!");
    }
    // write '0'
    if( write(fd, c, 1) != 1) {
        err_sys("write error!");
    }
    close(fd);
    // open file
    if((fd = open("a.txt", O_RDWR)) < 0) {
        err_sys("open error!");
    }

    TELL_WAIT();
    // fork
    if((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid == 0) {    /* 子进程 */
        is_continue = 1;
        while(is_continue) {
            if (pr_number(fd, 0) < 0)
                is_continue = 0;

            // 子进程写完，等待父进程
            TELL_PARENT(getppid());
            WAIT_PARENT();
        }

        exit(0);
    }
    else {  /* 父进程 */
        is_continue = 1;
        while (is_continue) {
            // 等待子进程写入
            WAIT_CHILD();

            if(pr_number(fd, 1) < 0)
                is_continue = 0;

            // 告诉子进程写完了
            printf("tell child\n");
            TELL_CHILD(pid);
        }

        exit(0);
    }

    exit(0);
}