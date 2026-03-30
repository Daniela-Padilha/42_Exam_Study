#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>

int id[200000], max = 0, next_id = 0;
fd_set activefds, writefds, readfds;
char *msg[200000], buffer_r[200000], buffer_w[200000];

void err(int flag)
{
	char *str;
	int len;

	if (flag == 0)
		str = "Wrong number of arguments\n";
	else if (flag == 1)
		str = "Fatal error\n";
	len = strlen(str);
	write(2, str, len);
	exit(1);
}

void broadcast(int sender_fd, char *buff)
{
	for (int i = 0; i <= max; i++)
	{
		if (i != sender_fd && FD_ISSET(i, &writefds))
			send(i, buff, strlen(buff), 0);
	}
	bzero(&buff, sizeof(buff));
}

void add_client(int fd)
{
	if (fd > max)
		max = fd;
	id[fd] = next_id++;
	msg[fd] = NULL;
	FD_SET(fd, &activefds);
	sprintf(buffer_w, "server: client %d just arrived\n", id[fd]);
	broadcast(fd, buffer_w);
}

void rm_client(int fd)
{
	sprintf(buffer_w, "server: client %d just left\n", id[fd]);
	broadcast(fd, buffer_w);
	id[fd] = -1;
	if (msg[fd])
		free(msg[fd]);
	msg[fd] = NULL;
	FD_CLR(fd, &activefds);
	close(fd);
}

void send_msg(int fd)
{
	char *buff;

	while(extract_message(&msg[fd], &buff) == 1)
	{
		sprintf(buffer_w, "client %d: ", id[fd]);
		broadcast(fd, buffer_w);
		broadcast(fd, buff);
		free(buff);
	}
}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


int main(int ac, char **av) {
	int sockfd;
	struct sockaddr_in servaddr, cli;

	if (ac != 2)
		err(0);

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		err(1);
	bzero(&servaddr, sizeof(servaddr));
	bzero(&cli, sizeof(cli));
	bzero(&buffer_w, sizeof(buffer_w));
	FD_ZERO(&activefds);

	// assign IP, PORT
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		err(1);
	if (listen(sockfd, 10) != 0)
		err(1);

	FD_SET(sockfd, &activefds);
	max = sockfd;
	
	while (1)
	{
		writefds = readfds = activefds;
		if (select(max + 1, &readfds, &writefds, NULL, NULL) == -1)
			continue;
		for (int fd = 0; fd <= max; fd++) 
		{
			if (!FD_ISSET(fd, &readfds))
				continue;
			//is server, accept clients
			if (fd == sockfd)
			{
				socklen_t len = sizeof(cli);
				int clientfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (clientfd < 0)
					continue;
				add_client(clientfd);
				break ;
			}

			//is client
			else {
				bzero(&buffer_r, sizeof(buffer_r));
				int read = recv(fd, buffer_r, sizeof(buffer_r), 0);
				
				//disconnect
				if (read <= 0)
				{
					rm_client(fd);
					break ;
				}

				//send message to server
				else
				{
					buffer_r[read] = 0;
					msg[fd] = str_join(msg[fd], buffer_r);
					send_msg(fd);
				}
			}
		}
	}
	return 0;
}
