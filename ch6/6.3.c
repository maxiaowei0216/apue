#include "apue.h"
#include <sys/utsname.h>

int main(void)
{
    struct utsname name = {0};

    if(uname(&name) == -1)
    {
        err_sys("uname error!");
    }

    printf("sysname = %s, nodename = %s\n", name.sysname, name.nodename);
    printf("release = %s\n", name.release);
    printf("version = %s\n", name.version);
    printf("machine = %s\n", name.machine);

    exit(0);
}