#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_clients {
	int	id;
	char msg[100000];
} t_clients;

// global variables
fd_set activefds, readfds, writefds;
int max_fd = 0;
int	c_id = 0;
t_clients clients[1024]; // default maximum number of open fds on Linux
char buffer_r[120000], buffer_w[120000];


// print to stderr
void err(int fatal)
{
	char *str;
	int len;

	if (fatal == 1)
		str = "Fatal error\n";
	else if (fatal == 0)
		str = "Wrong number of arguments\n";
	len = strlen(str);
	write(STDERR_FILENO, str, len);
	exit(1);
}

// send msg to all clients
void broadcast(int sender_fd, char *str)
{
	for (int i = 0; i <= max_fd; i++)
	{
		//if current fd is not sender and is in writefds
		if (FD_ISSET(i, &writefds) && i != sender_fd)
			send(i, str, strlen(str), 0);
	}
}

int main(int ac, char **av)
{
	int sockfd;
	struct sockaddr_in servaddr;

	// arg validation
	if (ac != 2)
		err(0);

	// socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		err(1);
	
	// clear activefds and add sockfd to fd_set struct
	max_fd = sockfd;
	FD_ZERO(&activefds);
	FD_SET(sockfd, &activefds);

	// assign IP and PORT
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	socklen_t len = sizeof(servaddr);

	// Bind newly created socket to IP and PORT
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		err(1);

	// set socket as ready to listen for clients
	if (listen(sockfd, 10) != 0)
		err(1);
	
	// main loop
	while (1)
	{
		// readfds and writefds are modified by select()
		// activefds stores the real nbr of active clients
		readfds = writefds = activefds;

		//  monitor clients activity
		if (select(max_fd + 1, &readfds, &writefds, 0, 0) == -1)
			continue;

		// loop trough all fds
		for (int fd = 0; fd <= max_fd; fd++)
		{
			// check if current fd is present in fd_set
			// if not present skip
			if (FD_ISSET(fd, &readfds) == 0)
				continue;
			
			// if the current fd is the server
			if (fd == sockfd)
			{
				// await a connection and create new socket for client
				int clientfd = accept(sockfd, (struct sockaddr *)&servaddr, &len);
				if (clientfd < 0)
					continue;
				
				// if a connection/msg is recieved
				if (clientfd > max_fd)
					max_fd = clientfd;
				clients[clientfd].id = c_id++;
				FD_SET(clientfd, &activefds);
				sprintf(buffer_w, "server: client %d just arrived\n", clients[clientfd].id);
				broadcast(clientfd, buffer_w);
			}

			// if the current fd is a client
			else
			{
				int read = recv(fd, buffer_r, 100000, 0);
				
				// if error or client disconnected
				if (read <= 0)
				{
					sprintf(buffer_w, "server: client %d just left\n", clients[fd].id);
					broadcast(fd, buffer_w);
					FD_CLR(fd, &activefds);
					close(fd);
				}

				// if client sent msg
				else
				{
					for (int i = 0, j = strlen(clients[fd].msg); i < read; i++, j++)
					{
						//append the msg inside buffer_r to clients.msg
						clients[fd].msg[j] = buffer_r[i];

						// look for \n
						if (clients[fd].msg[j] == '\n')
						{
							// replace \n with NULL
							clients[fd].msg[j] = 0;
							sprintf(buffer_w, "client %d: %s\n", clients[fd].id, clients[fd].msg);
							broadcast(fd, buffer_w);
							
							//clear clients.msg before writing next line
							memset(clients[fd].msg, 0, sizeof(clients[fd].msg));
							j = -1;
						}
					}
				}
			}
		}
	}
	return (0);
}

