/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:15:49 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/13 18:43:36 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void cleanup(int fd)
{
	if (fd >= 0)
		close(fd);
}

int picoshell(char **cmds[])
{
	pid_t	pid;
	int 	pipefd[2];
	int		prev_read = -1;
	int		i = 0;

	if (!cmds)
		return (1);
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(pipefd) == -1)
			{
				cleanup(pipefd[0]);
				cleanup(pipefd[1]);
				cleanup(prev_read);
				return (1);
			}
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		pid = fork();
		if (pid == -1)
		{
			cleanup(prev_read);
			cleanup(pipefd[0]);
			cleanup(pipefd[1]);
			return (1);
		}
		if (pid == 0)
		{
			if (prev_read != -1)
				dup2(prev_read, STDIN_FILENO);
			if (pipefd[1] != -1)
				dup2(pipefd[1], STDOUT_FILENO);
			cleanup(pipefd[0]);
			cleanup(pipefd[1]);
			cleanup(prev_read);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		cleanup(prev_read);
		cleanup(pipefd[1]);
		prev_read = pipefd[0];
		i++;
	}
	while (wait(NULL) != -1)
		;
	cleanup(prev_read);
	cleanup(pipefd[0]);
	cleanup(pipefd[1]);
	return (0);
}

// #include <stdio.h>
// int main (void)
// {
// 	char *cmd1[] = {"echo", "hello", NULL};
// 	char *cmd2[] = {"grep", "h", NULL};
// 	char *cmd3[] = {"wc", "-w", NULL};
// 	char **cmds[] = {cmd1, cmd2, cmd3, NULL};
// 	int res = picoshell(cmds);

// 	if (res)
// 		perror ("failure\n");
// 	else
// 		printf("success\n");
// 	exit (0);
// }