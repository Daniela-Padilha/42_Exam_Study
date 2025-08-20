/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:39:12 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/20 19:35:33 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

int parse_int(json *dst, FILE *stream)
{
	dst->type = INTEGER;
	if (fscanf(stream, "%i", &dst->integer) != 1)
	{
		unexpected(stream);
		return -1;
	}
	return 1;
}

int parse_str(json *dst, FILE *stream)
{
	size_t len = 0;
	size_t max = 16;
	int c;
	
	dst->type = STRING;
	(void)getc(stream);
	dst->string = malloc(max);
	if (!dst->string)
		return -1;
	while ((c = getc(stream)) != EOF && c != '"')
	{
		if (c == '\\')
		{
			c = getc(stream);
			if (c == EOF)
				break ;
		}
		if (len + 1 >= max)
			dst->string = realloc(dst->string, (max *= 2));
		dst->string[len] = c;
		len++;
	}
	if (c != '"')
	{
		unexpected(stream);
		free(dst->string);
		return -1;
	}
	dst->string[len] = '\0';
	return 1;
}

int parse_map(json *dst, FILE *stream)
{
	if (!expect(stream, '{'))
		return -1;
	
	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;
	
	while (peek(stream) != EOF && peek(stream) != '}')
	{
		dst->map.data = realloc(dst->map.data, sizeof(pair) * (dst->map.size + 1));
		if (!dst->map.data)
			return -1;
		pair *p = &dst->map.data[dst->map.size];
		json s_key;
		if (parse_string(&s_key, stream) != 1)
			return -1;
		p->key = s_key.string;
		if (!expect(stream, ':'))
			return -1;
		if (argo(&p->value, stream) != 1)
			return -1;
		dst->map.size++;
		if (!accept(stream, ','))
			break ;
	}
	if (!except(stream, '}'))
		return -1;
	return 1;
}

int		argo(json *dst, FILE *stream)
{
	int c = peek(stream);
	
	if (c == EOF)
	{
		unexpected(stream);
		return -1;
	}
	else if (isdigit(c))
		return (parse_int(dst, stream));
	else if (c == '"')
		return (parse_str(dst, stream));
	else if (c == '{')
		return (parse_map(dst, stream));
	unexpected(stream);
	return -1;
}
