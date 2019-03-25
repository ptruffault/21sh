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

static void		ft_son(t_process *prev, t_process *tmp, t_tree *t, t_shell *sh)
{
	if (tmp->cmd && (tmp->pid = fork()) == 0)
	{
		if ((prev && !ft_link_stdin(prev->pipe))
			|| (tmp->grp && !ft_link_stdout(tmp->pipe)))
			ft_exit_son(sh, 1);
		ft_execve(tmp, sh, t, 0);
	}
	else if (tmp->pid < 0)
		error("fork fucked up", tmp->cmd);
}

t_tree			*exec_pipe(t_tree *t, t_process *p, t_shell *sh)
{
	t_process	*prev;
	t_process	*tmp;

	prev = NULL;
	tmp = p;
	while (tmp)
	{
		ft_son(prev, tmp, t, sh);
		tmp->status = RUNNING_FG;
		if (prev)
		{
			t = t->next;
			ft_close_pipe(prev->pipe);
		}
		prev = tmp;
		tmp = tmp->grp;

	}
	tmp = p;
	ft_reset_fd(sh);
	ft_wait(p, sh);
	return (t);
}
