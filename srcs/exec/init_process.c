/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 15:17:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static void			ft_init_fd(t_process *new, t_tree *t)
{
	new->save[0] = 0;
	new->save[1] = 1;
	new->save[2] = 2;
	new->fd[0] = 0;
	new->fd[1] = 1;
	new->fd[2] = 2;
	new->status = t->o_type == O_BACK ? RUNNING_BG : RUNNING_FG;
	new->ret = -1;
	new->pid = 0;
}

static t_process	*ft_abort(t_process *p)
{
	if (p->builtins == TRUE)
		ft_reset_fd(p->save);
	if (p->argv)
		ft_freestrarr(p->argv);
	free(p);
	return (NULL);
}

t_process			*init_process(t_tree *t, t_shell *sh)
{
	t_process	*new;

	new = NULL;
	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		ft_init_fd(new, t);
		if (!(new->argv = ft_twordto_arr(t->cmd)))
			return (ft_abort(new));
		if (check_builtin(*new->argv) && (new->cmd = ft_strdup(*new->argv)))
		{
			new->builtins = TRUE;
			if (t->r)
				ft_redirect_builtin(t, new);
		}
		else if ((new->cmd = get_bin_path(*new->argv, sh->env)))
			new->builtins = FALSE;
		else
			return (ft_abort(new));
		new->next = sh->process;
		sh->process = new;
	}
	return (new);
}
