/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void ft_free_tree(t_tree *t)
{
	t_tree *tmp;

	while (t)
	{
		ft_freestrarr(t->arr);
		ft_strdel(&t->r.s);
		ft_strdel(&t->r.path);
		tmp = t->next;
		free(t);
		t = tmp;
	}
}

void print_tree(t_tree *t)
{
	ft_putstr("instruc = ");
	ft_putstrarr(t->arr);
	ft_putchar('\n');
	if (t->r.s)
	{
		ft_putstr("redirection = ");
		ft_putstr(t->r.s);
		printf("from %i -> to %i\n",t->r.from, t->r.to );
		if (t->r.path)
		{
			ft_putchar('\t');
			ft_putendl(t->r.path);
		}
	}
	if (t->l)
	{
		printf("link %c\n", t->l);
		
	}
	ft_putchar('\n');
}

t_tree *new_tree(void)
{
	t_tree *n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->arr = NULL;
	n->r.s = NULL;
	n->r.to = -2;
	n->r.from = 1;
	n->l = 0;
	n->r.path = NULL;
	n->next = NULL;
	return (n);
}

static char *get_binpath(char **input, t_envv *e, int *i)
{
	int inf;
	char *ret;

	ret = NULL;
	if ((inf = check_builtin(&input[*i])))
		 ret = ft_strdup(input[*i]);
	else if (inf == 0)
		 ret = check_bin(input[*i], e);
	*i = *i + 1;
	if (!ret)
		while ((input[*i]) && !IS_EOI(input[*i]) && !IS_PIPE(input[*i]))
			*i = *i + 1;
	return (ret);
}


char **get_cmd_and_arg(char **input, t_envv *e, int *i)
{
	char **ret;
	int len;
	int j;

	len = 0;
	j = 1;
	while (input[*i + len] && !IS_SYNTAX(input[*i + len]))
		len++;
	if (!(ret = (char **)malloc(sizeof(char *) *(len + 1)))
	|| (!(ret[0] = get_binpath(input, e, i))))
	{
		ft_freestrarr(ret);
		*i = *i + len;
		return (NULL);
	}
	while (j < len)
	{
		ret[j++] = ft_strdup(input[*i]);
		*i = *i + 1;
	}
	ret[j] = NULL;
	return (ret);
}




