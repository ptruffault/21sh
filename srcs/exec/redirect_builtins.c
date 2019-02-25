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

	r = t->r;
	while (r)
	{
		if (get_destination_fd(r) < 0)
			return (-1);
		if (IS_STD(r->from) && IS_STD(p->save[r->from]))
			p->save[r->from] = dup(r->from);
		if (IS_STD(r->to) && IS_STD(p->save[r->to]))
			p->save[r->to] = dup(r->to);
		if (fd_dup(r->to, r->from) < 0)
			error("redirection failed", NULL);
		r = r->next;
	}
	return (0);
}

void		ft_reset_fd(int fd[3])
{
	int	i;

	i = -1;
	while (++i <= 2)
		fd[i] = fd_dup(fd[i], i);
}
