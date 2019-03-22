/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:06 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

t_word	*ft_free_tword(t_word *w)
{
	t_word	*tmp;

	while (w)
	{
		ft_strdel(&w->word);
		tmp = w->next;
		free(w);
		w = NULL;
		w = tmp;
	}
	return (NULL);
}

t_redirect	*ft_free_redirection(t_redirect *r)
{
	t_redirect	*tmp;

	while (r)
	{
		tmp = r->next;
		ft_strdel(&r->heredoc);
		ft_strdel(&r->path);
		free(r);
		r = NULL;
		r = tmp;
	}
	return (NULL);
}

t_tree	*ft_free_tree(t_tree *t)
{
	t_tree	*tmp;

	while (t)
	{
		ft_free_tword(t->cmd);
		if (t->r)
			ft_free_redirection(t->r);
		tmp = t->next;
		free(t);
		t = tmp;
	}
	return (NULL);
}

t_hist	*ft_free_thist(t_hist *h)
{
	t_hist *tmp;

	while (h)
	{
		ft_strdel(&h->s);
		tmp = h->next;
		free(h);
		h = tmp;
	}
	return (NULL);
}

t_process	*ft_free_tprocess(t_process *p)
{
	t_process *tmp;

	while (p)
	{
		tmp = p->next;
		ft_strdel(&p->cmd);
		ft_freestrarr(&p->argv);
		ft_freestrarr(&p->env);
		if (p->grp)
			p->grp = ft_free_tprocess(p->grp);
		free(p);
		p = tmp;
	}
	return (NULL);
}
