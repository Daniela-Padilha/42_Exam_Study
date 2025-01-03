/*Assignment name	: ft_strspn
Expected files	: ft_strspn.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the strspn function 
(man strspn).

The function should be prototyped as follows:

size_t	ft_strspn(const char *s, const char *accept);*/

#include <stddef.h>

size_t ft_strspn(const char *s, const char *accept)
{
	size_t i = 0;
	size_t j = 0;
	size_t count = 0;

	while (s[i])
	{
		while (accept[j] && s[i] != accept[j])
			j++;
		if (accept[j] == '\0')
			return (count);
		j = 0;
		count++;
		i++;
	}
	return (count);
}
