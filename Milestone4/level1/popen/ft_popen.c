/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:23:40 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/13 15:02:25 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	pid_t pid;
	int pipefd[2];

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (type == 'r')
	{
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			execvp(file, argv);
			exit(-1);
		}
		else
		{
			close(pipefd[1]);
			return (pipefd[0]);
		}
	}
	if (type == 'w')
	{
		if (pid == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execvp(file, argv);
			exit(-1);
		}
		else
		{
			close(pipefd[0]);
			return (pipefd[1]);
		}
	}
	return (-1);
}

// int main() 
// {
//     int fd_ls = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     int fd_grep = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'w');
//     char line[1024];
// 	int bytes;

// 	if (fd_ls == -1 || fd_grep == -1)
// 		return (-1);
// 	while ((bytes = read(fd_ls, line, 1024)) > 0)
// 		write(fd_grep, line, bytes);
// 	close(fd_ls);
// 	close(fd_grep);
// 	return(0);
// }
