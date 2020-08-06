#include "apue.h"
#include <errno.h>

// 1-31号信号
const char *sig_str[]={"","SIGHUP","SIGINT","SIGQUIT","SIGILL","SIGTRAP","SIGABRT",      /* 0-6   */
                    "SIGBUS","SIGFPE","SIGKILL","SIGUSR1","SIGSEGV","SIGUSR2","SIGPIPE", /* 7-13  */
                    "SIGALRM","SIGTERM","SIGSTKFLT","SIGCHLD","SIGCONT","SIGSTOP",       /* 14-19 */
                    "SIGTSTP","SIGTTIN","SIGTTOU","SIGURG","SIGXCPU","SIGXFSZ",          /* 20-25 */
                    "SIGVTALRM","SIGPROF","SIGWINCH","SIGPOLL","SIGPWR","SIGSYS"};       /* 26-31 */

void
my_pr_mask(const char *str)
{
	sigset_t	sigset;
	int			errno_save, i;

	errno_save = errno;		/* we can be called by signal handlers */
	if (sigprocmask(0, NULL, &sigset) < 0) {
		err_ret("sigprocmask error");
	} else {
		printf("%s", str);
        for(i = 1; i < 32; i++) {
            if(sigismember(&sigset, i))
                printf(" %s", sig_str[i]);
        }

		printf("\n");
	}

	errno = errno_save;		/* restore errno */
}

int main()
{
    sigset_t newmask, oldmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    sigaddset(&newmask, SIGCONT);
    sigaddset(&newmask, SIGUSR1);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("sigprocmask error");

    my_pr_mask("my_pr_mask:");

    exit(0);
}