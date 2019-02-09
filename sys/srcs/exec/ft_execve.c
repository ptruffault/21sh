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

pid_t		ft_execve(t_process *p, t_tree *t, t_shell *sh)
{
	pid_t	pid;
	char	**env;
	char	*bin_path;

	bin_path = ft_strdup(p->cmd);
	env = tenvv_to_tab(sh->env);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", bin_path);
	else if (pid == 0)
	{
		ft_redirect(t);
		execve(bin_path, p->argv, env);
		warning("execve fucked up", bin_path);
	}
	ft_freestrarr(env);
	ft_strdel(&bin_path);
	return (pid);
}

t_process	*init_process(t_tree *t, t_shell *sh)
{
	t_process	*new;

	new = NULL;
	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		if (t->o_type == O_BACK)
			new->status = RUNNING_BG;
		else
			new->status = RUNNING_FG;
		new->ret = -1;
		new->pid = 0;
		if (!(new->argv = ft_twordto_arr(t->cmd)))
		{
			free(new);
			return (NULL);
		}
		new->next = sh->process;
		sh->process = new;
	}
	return (new);
}

int			ft_exec(t_tree *t)
{
	t_process	*p;
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if ((p = init_process(t, sh)))
	{
		if (check_builtin(*p->argv))
		{
			p->cmd = ft_strdup(*p->argv);
			p->ret = run_builtin(t, p->argv);
			p->status = DONE;
		}
		else if ((p->cmd = get_bin_path(*p->argv, sh->env)))
		{
			p->pid = ft_execve(p, t, sh);
			if (p->status == RUNNING_FG)
			{
				wait(&p->ret);
				if (p->status != KILLED)
					p->status = DONE;
			}
		}
	}
	ft_freestrarr(p->argv);
	return (p->ret);
}
