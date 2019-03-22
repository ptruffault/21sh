/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>


static int		ft_link_stdin(int pipe[2])
{
	if (dup2(pipe[0], STDIN_FILENO) < 0)
		return (-1);
	return (ft_close(pipe[1]));
}

static int		ft_link_stdout(int pipe[2])
{
	if (dup2(pipe[1], STDOUT_FILENO) < 0)
		return (-1);
	return (ft_close(pipe[0]));
}

static int		ft_close_pipe(int pipe[2])
{
	if (!ft_close(pipe[0])
	|| !ft_close(pipe[1]))
		return (0);
	return (1);
}

/* 
static int		ft_exec_son(t_process *p, t_tree *t, t_shell *sh)
{
	int exit_code;

	exit_code = -1;
	if (!t->r || (t->r && ft_redirect_builtin(t, p, sh)))
	{
		if (p->builtins == TRUE)
			exit_code = run_builtin(t, p->argv, sh);
		else if (p->cmd && !ft_isempty(p->cmd))
		{
			execve(p->cmd, p->argv, p->env);
			error("execve fucked up", p->cmd);
		}
		else
			error("command not found", *p->argv);
	}
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(exit_code);
}*/

int 	ft_get_pgid(int pgid, t_process *p, t_process *prev)
{
	if (pgid == 0 && !prev)
		pgid = getpid();
	if ((!prev && pgid > 0 && (setpgid(pgid, 0)) < 0)
		|| (prev && pgid > 0 && setpgid(0, pgid) < 0))
	{
		warning("can't set pgid", p->cmd);
		perror(p->cmd);
	}
	return (pgid);
}


t_tree			*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;

	prev = NULL;
	tmp = p;
	while (tmp)
	{
		tmp->status = RUNNING_FG;
		if (tmp->cmd && (tmp->pid = fork()) == 0)
		{
			if  ((prev && !ft_link_stdin(prev->pipe))
			|| (tmp->grp && !ft_link_stdout(tmp->pipe)))
				ft_exit_son(t, sh, -1);
			ft_execve(tmp, sh, t, 0);
		}
		else if (tmp->pid < 0)
			error("fork fucked up", tmp->cmd);
		if (prev)
			ft_close_pipe(prev->pipe);
		prev = tmp;
		tmp = tmp->grp;
		t = t->next;
	}
	tmp = p;
	ft_wait(p, sh);
	ft_reset_fd(sh);
	return (t);
}

