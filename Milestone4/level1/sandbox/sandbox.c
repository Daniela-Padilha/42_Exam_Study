/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:25:27 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/13 22:17:34 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void alarm_handler(int sig)
{
	(void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;
	struct sigaction sa;

	sa.sa_handler = alarm_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGALRM, &sa, NULL) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		f();
		exit(0);
	}
	alarm(timeout);
	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
		{
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %i seconds\n", timeout);
			return (0);
		}
		return (-1);
	}
	alarm(0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		else
		{
			if (verbose)
				printf("Bad function: exited with code %i\n", WEXITSTATUS(status));
			return (0);
		}
	}
	if (WIFSIGNALED(status))
	{
		if (verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		return (0);
	}
	return (-1);
}

// void nice_func()
// {
// 	return ;
// }

// void bad_exit()
// {
// 	exit(1);
// }

// void timeout()
// {
// 	while(1)
// 		;
// }

// void segfault()
// {
// 	int *p = NULL;
// 	*p = 10;
// }

// void sigkill()
// {
// 	sleep(5);
// }

// int main()
// {
// 	int r;

// 	r = sandbox(nice_func, 5, true);
// 	printf("res is %d\n", r);
// 	r = sandbox(bad_exit, 5, true);
// 	printf("res is %d\n", r);
// 	r = sandbox(segfault, 5, true);
// 	printf("res is %d\n", r);
// 	r = sandbox(timeout, 5, true);
// 	printf("res is %d\n", r);
// 	r = sandbox(sigkill, 1, true);
// 	printf("res is %d\n", r);
// 	return 0;
// }
