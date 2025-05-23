/* Assignment name  : ft_split
Expected files   : ft_split.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);*/

#include <stdlib.h>

char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = 0;

	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}


char    **ft_split(char *str)
{
	char **words;
	int i = 0;
	int j = 0;
	int k = 0;
	int wc = 0;

	
	while (str[i])
	{
		while (str[i] == ' ' || ((str[i]) >= 9 && str[i] <= 13))
			i++;
		if (str[i])
			wc++;
		while (str[i] != ' ' && (!((str[i]) >= 9 && str[i] <= 13)))
			i++;
	}		
	words = (char **)malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' '|| ((str[i]) >= 9 && str[i] <= 13)))
			i++;
		j = i;
		while (str[i] && (str[i] != ' ' && (!((str[i]) >= 9 && str[i] <= 13))))
			i++;
		if (i > j)
		{
			words[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(words[k++], &str[j], (i - j));
		}
		words[k] = NULL;
	}
	return (words);
}
