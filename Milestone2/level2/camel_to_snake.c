/* Assignment name  : camel_to_snake
Expected files   : camel_to_snake.c
Allowed functions: malloc, free, realloc, write
--------------------------------------------------------------------------------

Write a program that takes a single string in lowerCamelCase format
and converts it into a string in snake_case format.

A lowerCamelCase string is a string where each word begins with a capital letter
except for the first one.

A snake_case string is a string where each word is in lower case, separated by
an underscore "_".

Examples:
$>./camel_to_snake "hereIsACamelCaseWord"
here_is_a_camel_case_word
$>./camel_to_snake "helloWorld" | cat -e
hello_world$
$>./camel_to_snake | cat -e
$ */

#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int i;
	int	j;
	char *str;

	while (av[1][i])
		{
			if (av[1][i] >= 'A' && av[1][i] <= 'Z')
				j++;
			i++;
		}
	str =(char *)malloc((i * sizeof(char)) + j);
	if (ac == 2)
	{
		i = 0;
		j = 0;
		while (av[1][i])
		{
			if (av[1][i] >= 'a' && av[1][i] <= 'z')
			{
				str[j] = write(1, &str[j], 1);
			}
			else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
			{
				str[j] = '_';
				j++;
				str[j] = av[1][i] + 32;
				write(1, &str[j], 1);
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}

NOT FINISHED
