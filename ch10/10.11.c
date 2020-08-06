/**
 * Ubuntu20.04.1中似乎没发生错误
 * 
 **/
#include "apue.h"

#define	BUFFSIZE	100

static void signal_intr1(int no)
{
    printf("\n*************SIGXFSZ*************** \n");
}

int
main(void)
{
	int		n, rn;
	char	buf[BUFFSIZE];

    if (signal(SIGXFSZ, signal_intr1) == SIG_ERR)
        err_sys("signal(SIGXFSZ) error");

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if ((rn = write(STDOUT_FILENO, buf, n)) != n){
            printf("\n***************write return:%d***************n", rn);
		}

	}

	if (n < 0)
		err_sys("read error");

	exit(0);
}