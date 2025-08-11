#include "get_next_line.h"

char *ft_join(char *str, char c, int len);

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_len = 0;
	static int index = 0;
	char *line;
	int i = 0;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = (char *)malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		if (index >= buffer_len)
		{
			buffer_len = read(fd, buffer, BUFFER_SIZE);
			index = 0;
			if (buffer_len <= 0)
			{
				if (i == 0)
				{
					free(line);
					return (NULL);
				}
			}
			break;
		}
		line = ft_join(line, buffer[index++], i);
		if (!line)
			return (NULL);
		if (line[i] == '\n')
			break;
		i++;
	}
	return (line);
}

char *ft_join(char *str, char c, int len)
{
	char *new_str;
	int i;

	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[++i] = '\0';
	free(str);
	return (new_str);
}

// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	int fd;
// 	char *path = av[1];
// 	char *line;

// 	fd = open(path, O_RDONLY);
// 	(void)ac;
// 	if (fd < 0)
// 		return (0);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
