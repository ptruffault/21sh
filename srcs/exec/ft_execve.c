/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:02:44 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:02:48 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

pid_t		ft_execve(t_process *p, t_shell *sh)
{
	pid_t	pid;
	char	**env;

	env = tenvv_to_tab(sh->env);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", p->cmd);
	else if (pid == 0)
	{
		execve(p->cmd, p->argv, env);
		warning("execve fucked up", p->cmd);
	}
	ft_freestrarr(env);
	return (pid);
}

int			ft_exec(t_tree *t, t_process *p)
{
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (p->builtins == TRUE)
	{
		p->ret = run_builtin(t, p->argv);
		p->status = DONE;
	}
	else
	{
		p->pid = ft_execve(p, sh);
		if (p->status == RUNNING_FG)
		{
			wait(&p->ret);
			if (p->status != KILLED)
				p->status = DONE;
		}
	}
	return (p->ret);
}
