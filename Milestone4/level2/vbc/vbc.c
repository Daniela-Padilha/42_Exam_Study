/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:50:25 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/18 23:27:33 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vbc.h"

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
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

int accept(char **s, char c)
{
    if (**s)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int prev_check(char *s)
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

node    *parse_nbrs(char **s)
{
	if (**s >= '0' && **s <= '9')
    {
		node new;
		new.type = VAL;
		new.val = **s - '0';
		new.l = NULL;
		new.r = NULL;
		(*s)++;
		return (new_node(new));
	}
	else if (**s == '(')
    {
		(*s)++;
		node *in = parse_add(s);
		if (!expect(s, ')'))
		{
			destroy_tree(in);
			return NULL;
		}
		return in;
	}
	else
    {
        unexpected(**s);
        return NULL;
    }
}

node    *parse_multi(char **s)
{

}

node    *parse_add(char **s)
{
    node *new;
	int i = 0;

	while (s[i])
	{
		if (s[i] == '+')
		{
			
		}
		i++;
	}

    if (*s) 
    {
        destroy_tree(ret);
        return (NULL);
    }
    return (ret);
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
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
	return (0);
}
