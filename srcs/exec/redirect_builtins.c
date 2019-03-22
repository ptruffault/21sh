/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:17:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int			ft_redirect_builtin(t_tree *t, t_process *p, t_shell *sh)
{
	t_redirect *r;

	r = t->r;
	while (r)
	{
		if (!get_destination_fd(r))
			return (0);
		if (IS_STD(r->from) && IS_STD(sh->std[r->from]))
			sh->std[r->from] = dup(r->from);
		if (IS_STD(r->to) && IS_STD(sh->std[r->to]))
			sh->std[r->to] = dup(r->to);
		if (fd_dup(r->to, r->from, p, 1) < 0)
			return (0);
		if (IS_STD(r->from))
			p->fd[r->from] = r->to;
		r = r->next;
	}
	return (1);
}

void		ft_reset_fd(t_shell *sh)
{
	int	i;
	int std[3];

	i = -1;
	std[0] = STDIN_FILENO;
	std[1] = STDOUT_FILENO;
	std[2] = STDERR_FILENO;
	while (++i <= 2)
	{
		if (sh->std[i] != std[i])
		{
			if (dup2(sh->std[i], std[i]) < 0)
				error_i("can't load old fd", i);
			ft_close(sh->std[i]);
			sh->std[i] = std[i];
		}
	}
}
