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

#include <parseur.h>

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
