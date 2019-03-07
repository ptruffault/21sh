/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:52:08 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static void	ft_son(t_tree *t, t_process *p, t_shell *sh)
{
	if (p->cmd)
	{
		execve(p->cmd, p->argv, p->env);
		warning("execve fucked up", p->cmd);
	}
	else
		error("command not found", t->cmd->word);
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(-1);
}

void		ft_execve(t_process *p, t_shell *sh, t_tree *t)
{
	if (t->r && !ft_redirect_builtin(t, p))
			return ;
	if (p->builtins == TRUE)
	{
		p->ret = run_builtin(t, p->argv);
	}
	else if ((p->pid = fork()) == -1)
		warning("fork failed to create a new process", p->cmd);
	else if (p->pid == 0)
		ft_son(t, p, sh);
}

