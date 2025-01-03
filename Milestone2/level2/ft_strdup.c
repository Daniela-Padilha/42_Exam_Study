/* Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
 */
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int i = 0;
	int len = 0;
	char *s;

	while (src[len])
		len++;
	s = malloc((len * sizeof(char)) + 1);
	if (s != NULL)
	{
		while (src[i])
		{
			s[i] == src[i];
			i++
		}
		s[i] = '\0';
	}
	return (s);
}
