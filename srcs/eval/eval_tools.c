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

void ft_free_redirection(t_redirect *r)
{
	t_redirect *tmp;

	while (r)
	{
		tmp = r->next;
		ft_strdel(&r->path);
		free(r);
		r = NULL;
		r = tmp;
	}
}

void ft_free_tree(t_tree *t)
{
	t_tree *tmp;

	while (t)
	{
		ft_freestrarr(t->arr);
		ft_free_redirection(t->r);
		tmp = t->next;
		free(t);
		t = tmp;
	}
}

void put_redirect(t_redirect *r)
{
	t_redirect *tmp;

	tmp = r;
	while (tmp)
	{
		printf("type = %i path = %s from = %i to = %i \n",tmp->t, tmp->path, tmp->from, tmp->to );
		tmp = tmp->next;
	}
}

void print_tree(t_tree *t)
{
	t_tree *tmp;
	tmp = t;
	while (tmp)
	{
		ft_putstr("instruc = ");
		if (tmp->arr)
			ft_putstrarr(tmp->arr);
		if (tmp->r)
			put_redirect(tmp->r);	
		if (tmp->l)
		{
			ft_putstr("link : ");
			ft_putchar(tmp->l);
		}
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

t_tree *new_tree(void)
{
	t_tree *n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->arr = NULL;
	n->r = NULL;
	n->l = 0;
	n->ret = 0;
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




