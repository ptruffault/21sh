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
	int ret;

	r = t->r;
	while (r)
	{
		if (get_destination_fd(r) < 0)
			return (-1);
		if (IS_STD(r->from) && IS_STD(p->save[r->from]))
			p->save[r->from] = dup(r->from);
		printf("%i -> %i\n",r->from, r->to );
		if ((ret = fd_dup(r->to, r->from)) == -1)
		{
			error("redirection failed", NULL);
			return (-1);
		}
		if (IS_STD(r->to) && IS_STD(r->from))
		{
			p->fd[r->to] = r->from;
		}
		printf("in = %i\nout = %i\nerr = %i\n",p->fd[0], p->fd[1], p->fd[2] );
		r = r->next;
	}
	return (0);
}

void		ft_reset_fd(int fd[3])
{
	int	i;
	int	tmp;

	i = 0;
	while (i <= 2)
	{
		if (fd[i] != i)
		{
			ft_close(i);
			if ((tmp = dup(fd[i])) == -1)
				error("can't load old fd", NULL);
			ft_close(fd[i]);
			fd[i] = tmp;
		}
		i++;
	}
}
