/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:50:25 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/20 17:15:01 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

int g_index = 0;

node    *new_node(char value)
{
    node *n = malloc(sizeof(node));
    if (!n)
		return (NULL);
	n->l = NULL;
	n->r = NULL;
	if (value == '+')
	{
		n->type = ADD;
		n->val = 0;
	}
	else if (value == '*')
	{
		n->type = MULTI;
		n->val = 0;
	}
	else
	{
		n->type = VAL;
		n->val = value -'0';
	}
    return (n);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

// int accept(char **s, char c)
// {
//     if (**s)
//     {
//         (*s)++;
//         return (1);
//     }
//     return (0);
// }

// int expect(char **s, char c)
// {
//     if (accept(s, c))
//         return (1);
//     unexpected(**s);
//     return (0);
// }

int parenthesis(char *s)
{
	int open = 0;
	int i = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
			open--;
		i++;
	}
	if (open == 0)
		return 0;
	else if (open > 0)
	{
		unexpected(0);
		return -1;
	}
	else
	{
		unexpected(')');
		return -1;
	}
}

int prev_check(char *s)
{
	int i = 0;

	if (parentesis(s) == -1)
		return -1;
	while (s[i])
	{
		if (i == 0 && (s[i] == '+' || s[i] == '*'))
			return (printf("Unexpected token '%c'\n", s[i]), -1);
		else if (s[i] == '+' || s[i] == '*')
		{
			if (!s[i + 1])
				return (unexpected(0), -1);
			else if (!isdigit(s[i + 1]))
				return (printf("Unexpected token '%c'\n", s[i + 1]), -1);
		}
		if (isdigit(s[i]) && isdigit(s[i + 1]))
			return (printf("Unexpected token '%c'\n", s[i + 1]), -1);
		i++;
	}
	return 0;
}

node    *parse_nbrs(char *s)
{
	if (s[g_index] == '(')
	{
		g_index++;
		node *new = parse_add(s);
		if (s[g_index] == ')')
			g_index++;
		return (new);
	}
	else if (isdigit(s[g_index]))
	{
		node *new = new_node(s[g_index]);
		g_index++;
		return (new);
	}
	return (NULL);
}

node    *parse_multi(char *s)
{
	node *curr = parse_nbrs(s);
	while (s[g_index] == '*')
	{
		node *signal = new_node(s[g_index++]);
		signal->r = parse_nbrs(s);
		signal->l = curr;
		curr = signal;
	}
	return (curr);
}

node    *parse_add(char *s)
{
	node *curr = parse_multi(s);
	while (s[g_index] == '+')
	{
		node *signal = new_node(s[g_index++]);
		signal->r = parse_multi(s);
		signal->l = curr;
		curr = signal;
	}
	return (curr);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
	return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
		return (1);
	if (prev_check(argv[1]) == -1)
		return (1);
    node *tree = parse_add(argv[1]);
    if (!tree)
		return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
	return (0);
}
