/* Assignment name  : ft_itoa
Expected files   : ft_itoa.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes an int and converts it to a null-terminated string.
The function returns the result in a char array that you must allocate.

Your function must be declared as follows:

char	*ft_itoa(int nbr);*/

#include <stdlib.h>

int ndigits(int nbr)
{
	int i = 0;

	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr)
	{
		nbr = nbr /10;
		i++;
	}
	return(i);
}

char *ft_itoa(int nbr)
{
	char *res;
	int end = ndigits(nbr);

	res = (char *)malloc(sizeof(char) * end + 1);
	if (!res)
		return(NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		res[0] = '-';
	}
	if (nbr == 0)
		res[0] = '0';
	res[end] = '\0';
	while (nbr)
	{
		res[end - 1] = (nbr % 10) + '0';
		nbr = nbr / 10;
		end--;
	}
	return (res);
}
