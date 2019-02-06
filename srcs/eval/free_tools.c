/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

void ft_free_tword(t_word *w)
{
	t_word *tmp;

	while (w)
	{
		ft_strdel(&w->word);
		w->type = 0;
		tmp = w->next;
		free(w);
		w = NULL;
		w = tmp;
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

void ft_free_tree(t_tree *t)
{
	t_tree *tmp;

	while (t)
	{
		ft_free_tword(t->cmd);
		if (t->r)
			ft_free_redirection(t->r);
		tmp = t->next;
		free(t);
		t = tmp;
	}
}

void ft_free_thist(t_hist *h)
{
	t_hist *tmp;

	while (h)
	{
		ft_strdel(&h->s);
		tmp = h->next;
		free(h);
		h = tmp;
	}
}

void ft_free_tprocess(t_process *p)
{
	t_process *tmp;

	while (p)
	{
		tmp = p->next;
		ft_strdel(&p->cmd);
		free(p);
		p = tmp;
	}
}


void ft_free_tshell(t_shell *sh)
{
	ft_free_tenvv(sh->env);
	ft_free_tenvv(sh->intern);
	ft_free_tenvv(sh->alias);
	ft_free_tprocess(sh->process);
	ft_free_thist(sh->hist);
}
