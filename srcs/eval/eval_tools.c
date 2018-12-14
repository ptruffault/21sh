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

#include <21sh.h>


void ft_free_tword(t_word *w)
{
	t_word *tmp;

	while (w)
	{
		ft_strdel(&w->word);
		tmp = w->next;
		free(w);
		w = tmp;
	}
}

void ft_free_tree(t_tree *t)
{
	t_tree *tmp;

	while (t)
	{
		ft_freestrarr(t->arr);
		if (t->r)
			ft_free_redirection(t->r);
		tmp = t->next;
		free(t);
		t = tmp;
	}
}

void ft_free_redirection(t_redirect *r)
{
	t_redirect *tmp;

	while (r)
	{
		tmp = r->next;
		ft_strdel(&r->heredoc);
		ft_strdel(&r->path);
		free(r);
		r = NULL;
		r = tmp;
	}
}

t_word *new_tword(void)
{
	t_word *n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

t_tree *new_tree(void)
{
	t_tree *n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->arr = NULL;
	n->r = NULL;
	n->o_type = 0;
	n->ret = 0;
	n->next = NULL;
	n->fd[STDIN] = 0;
	n->fd[STDOUT] = 1;
	n->fd[STDERR] = 2;
	return (n);
}

t_redirect *new_redirection(void)
{
	t_redirect *new;

	if (!(new = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	new->t = 0;
	new->to = -2;
	new->from = -1;
	new->path = NULL;
	new->done = 0;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}



