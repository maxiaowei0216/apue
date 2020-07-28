#include "apue.h"
#include <sys/wait.h>

static void pr_siginfo(siginfo_t info)
{
    if(info.si_code == CLD_EXITED)
    {
        printf("normal termination, exit status = %d\n",info.si_status);
    }
    else if (info.si_code == CLD_STOPPED)
    {
        printf("child stopped, signal number = %d\n",info.si_status);
    }
    else
    {
        printf("abnormal termination, signal number = %d\n",info.si_status);
    }
    }

int
main(void)
{
	pid_t	pid;
	siginfo_t info;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)				/* child */
		exit(7);

	if (waitid(P_PID, pid, &info, WEXITED) != 0)		/* wait for child */
		err_sys("waitid error");
	pr_siginfo(info);				/* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)				/* child */
		abort();					/* generates SIGABRT */

	if (waitid(P_PID, pid, &info, WEXITED) != 0)		/* wait for child */
		err_sys("wait error");
	pr_siginfo(info);				/* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)				/* child */
		info.si_code /= 0;				/* divide by 0 generates SIGFPE */

	if (waitid(P_PID, pid, &info, WEXITED) != 0)		/* wait for child */
		err_sys("wait error");
	pr_siginfo(info);				/* and print its status */

	exit(0);
}