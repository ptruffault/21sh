/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:51:14 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static t_tree	*ft_end_of_pipe(t_tree *t, int pipes[2], int pid[2])
{
	ft_close(pipes[0]);
	ft_close(pipes[1]);
	if (pid[0] > 0 && pid[1] > 0)
	{
		waitpid(pid[0], 0, 0);
		waitpid(pid[1], 0, 0);
	}
	while (t->o_type == O_PIPE)
		t = t->next;
	return (t);
}

static void		ft_exec_next(t_tree *t, int pipes[2], t_shell *sh, t_process *p)
{
	(void)p;

	dup2(pipes[0], p->fd[0]);
	ft_close(pipes[1]);
	if (t->o_type == O_PIPE && t->next)
		t = exec_pipe(t);
	else
		t->ret = ft_exec(t, p);
	ft_reset_fd(p->fd);
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(0);
}

static void		ft_exec_son(t_tree *t, t_process *p, int pipes[2], t_shell *sh)
{
	dup2(pipes[1], p->fd[1]);
	close(pipes[0]);
	ft_exec(t, p);
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(0);
}

t_tree			*exec_pipe(t_tree *t)
{
	int			pipes[2];
	int			pid[2];
	t_process	*p1;
	t_process	*p2;
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	pid[0] = -1;
	pid[1] = -1;
	if (pipe(pipes) != 0)
		return (t);
	if (!(p1 = init_process(t, sh)) || (pid[0] = fork()) < 0)
	{
		error("fork filed to create a new process in pipe", t->cmd->word);
		return (ft_end_of_pipe(t, pipes, pid));
	}
	else if (pid[0] == 0)
		ft_exec_son(t, p1, pipes, sh);
	ft_reset_fd(p1->fd);
	if ( !(p2 = init_process(t->next, sh)) || (pid[1] = fork()) < 0)
	{
		error("fork filed to create a new process in pipe", t->cmd->word);
		return (ft_end_of_pipe(t, pipes, pid));
	}
	else if (pid[1] == 0)
		ft_exec_next(t->next, pipes, sh, p2);
	ft_reset_fd(p2->fd);
	return (ft_end_of_pipe(t, pipes, pid));
}
