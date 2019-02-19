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

pid_t		ft_execve(t_process *p, t_shell *sh, t_tree *t)
{
	pid_t	pid;
	char	**env;

	env = tenvv_to_tab(sh->env);
	pid = -1;
	if (p->builtins == TRUE)
		p->ret = run_builtin(t, p->argv);
	else if ((pid = fork()) == -1)
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
	p->pid = ft_execve(p, sh, t);
	if (p->status == RUNNING_FG)
	{
		if (p->builtins == FALSE)
			wait(&p->ret);
		else
			p->ret = 0;
		if (p->status != KILLED)
		{
			ft_reset_fd(p->fd);
			p->status = DONE;
		}
	}
	return (p->ret);
}
