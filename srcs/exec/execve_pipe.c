/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:48:31 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/04 11:48:33 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static void	ft_execv_son(t_process *p, t_tree *t)
{
	if (ft_redirect_builtin(t, p))
	{
		if (!p->cmd)
			error("unknow command", t->cmd->word);
		else if (p->builtins == TRUE)
			p->ret = run_builtin(t, p->argv);
		else if (p->cmd)
		{
			execve(p->cmd, p->argv, p->env);
			warning("execve fucked up", p->cmd);
		}
	}
}

void		ft_exec_son(t_process *p, t_tree *t)
{
	ft_execv_son(p, t);
	if (p->status == RUNNING_FG)
	{
		if (p->builtins == FALSE)
			wait(&p->ret);
		if (p->status != KILLED)
			p->status = DONE;
	}
}
