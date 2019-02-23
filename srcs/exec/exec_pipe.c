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

static t_tree	*ft_end_of_pipe(t_tree *t, t_process *p1, t_process *p2, int pid[2])
{
	if (pid[0] > 0 && pid[1] > 0)
	{
		waitpid(pid[0], &p1->ret, 0);
		p1->status = DONE;
		waitpid(pid[1], &p2->ret, 0);
		p2->status = DONE;
	}
	while (t->o_type == O_PIPE)
		t = t->next;
	return (t);
}

static void		ft_exec_next(t_tree *t, int pipes[2], t_shell *sh, t_process *p)
{
	int ret;

	dup2(pipes[0], STDIN_FILENO);
	ft_close(pipes[1]);
	if (t->next->o_type == O_PIPE && t->next->next)
	{
		exec_pipe(t->next);
		ret = t->next->ret;
	}
	else
		ret = ft_exec(t, p);
	ft_reset_fd(p->save);
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(ret);
}

static void		ft_exec_son(t_tree *t, t_process *p, int pipes[2], t_shell *sh)
{
	int ret;

	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[0]);
	ret = ft_exec(t, p);
	ft_reset_fd(p->save);
	ft_free_tshell(sh);
	ft_free_tree(t);
	exit(ret);
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
	p1 = NULL;
	p2 = NULL;
	if (!(p1 = init_process(t, sh)) || (pid[0] = fork()) < 0)
	{
		error("fork filed to create a new process in pipe", t->cmd->word);
		return (ft_end_of_pipe(t, p1, p2, pid));
	}
	else if (pid[0] == 0)
		ft_exec_son(t, p1, pipes, sh);
	if ((p2 = init_process(t->next, sh)) && (pid[1] = fork()) < 0)
	{
		error("fork filed to create a new process in pipe", t->cmd->word);
		return (ft_end_of_pipe(t, p1, p2, pid));
	}
	else if (pid[1] == 0)
		ft_exec_next(t, pipes, sh, p2);
	ft_close(pipes[0]);
	ft_close(pipes[1]);
	return (ft_end_of_pipe(t, p1, p2, pid));
}
