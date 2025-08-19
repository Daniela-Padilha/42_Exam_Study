/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddo-carm <ddo-carm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:46:32 by ddo-carm          #+#    #+#             */
/*   Updated: 2025/08/19 22:31:46 by ddo-carm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
# define VBC_H

# include <stdio.h>
# include <malloc.h>
# include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(char value);
void    destroy_tree(node *n);
void    unexpected(char c);
int     parenthesis(char *s);
int     prev_check(char *s);
node    *parse_nbrs(char *s);
node    *parse_multi(char *s);
node    *parse_add(char *s);
int eval_tree(node *tree);

#endif