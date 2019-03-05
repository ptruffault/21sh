/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:17:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:52:58 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int			ft_redirect_builtin(t_tree *t, t_process *p)
{
	t_redirect *r;

	if (!t->r)
		return (1);
	r = t->r;
	while (r)
	{
		if (!get_destination_fd(r))
		{
			error("can't set redirect", NULL);
			return (0);
		}
		if (IS_STD(r->from) && IS_STD(p->save[r->from]))
			p->save[r->from] = dup(r->from);
		if (IS_STD(r->to) && IS_STD(p->save[r->to]))
			p->save[r->to] = dup(r->to);
		if (fd_dup(r->to, r->from, p) < 0)
			return (0);
		if (IS_STD(r->from))
			p->fd[r->from] = r->to;
		r = r->next;
	}
	return (1);
}

void		ft_reset_fd(t_process *p)
{
	int	i;

	i = -1;
	while (++i <= 2)
	{
		if (p->save[i] != i)
		{
			p->fd[i] = dup2(p->save[i], i);
			ft_close(p->save[i]);
		}
	}
}
