/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:17:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:17:52 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int			ft_redirect_builtin(t_tree *t, int fd[3])
{
	t_redirect *r;

	r = t->r;
	while (r)
	{
		if (get_destination_fd(r) < 0)
			return (-1);
		if (IS_STD(r->from))
			fd[r->from] = dup(r->from);
		if (fd_dup(r->to, r->from, 0) == -1)
		{
			error("redirection failed", NULL);
			return (-1);
		}
		r = r->next;
	}
	return (0);
}

void		ft_reset_fd(int fd[3])
{
	int i;
	int tmp;

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
