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
	{
		if (t->r)
			ft_redirect_builtin(t, p);
		p->ret = run_builtin(t, p->argv);
	}
	else if ((pid = fork()) == -1)
		warning("fork failed to create a new process", p->cmd);
	else if (pid == 0)
	{
		if (t->r)
			ft_redirect_builtin(t, p);
		if (!p->cmd)
			error("unknow command",t->cmd->word);
		else
		{
			execve(p->cmd, p->argv, env);
			warning("execve fucked up", p->cmd);
		}
		ft_free_tshell(sh);
		ft_free_tree(ft_get_set_tree(NULL));
		exit(-1);
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
		ft_reset_fd(p->save);
		if (p->status != KILLED)
			p->status = DONE;
	}
	return (p->ret);
}
