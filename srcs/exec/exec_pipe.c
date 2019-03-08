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

static t_tree	*ft_end(t_tree *t, t_process *p1, t_process *p2, int pip[2])
{
	ft_close(pip[0]);
	ft_close(pip[1]);
	if (p1 && p2 && p1->pid > 0 && p2->pid > 0)
	{
		waitpid(p1->pid, &p1->ret, 0);
		p1->status = DONE;
		waitpid(p2->pid, &p2->ret, 0);
		p2->status = DONE;
	}
	while (t->o_type == O_PIPE)
		t = t->next;
	return (t);
}

static void		ft_exec_right(t_tree *t, int pip[2], t_shell *sh, t_process *p)
{
	dup2(pip[0], STDIN_FILENO);
	ft_close(pip[1]);
	if (t->next->o_type == O_PIPE && t->next->next)
		exec_pipe(t->next);
	else
		ft_exec_son(p, t->next, sh);
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	ft_close(pip[0]);
	exit(-1);
}

static void		ft_exec_left(t_tree *t, t_process *p, int pip[2], t_shell *sh)
{
	dup2(pip[1], STDOUT_FILENO);
	ft_close(pip[0]);
	ft_exec_son(p, t, sh);
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	ft_close(pip[1]);
	exit(-1);
}

t_tree			*exec_pipe(t_tree *t)
{
	int			pipes[2];
	t_process	*p1;
	t_process	*p2;
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (pipe(pipes) != 0)
		return (t);
	p1 = NULL;
	p2 = NULL;
	if (!(p1 = init_process(t, sh))
	|| (p1->pid = fork()) < 0)
		return (ft_end(t, p1, p2, pipes));
	else if (p1->pid == 0)
		ft_exec_left(t, p1, pipes, sh);
	if (!(p2 = init_process(t->next, sh))
	|| (p2->pid = fork()) < 0)
		return (ft_end(t, p1, p2, pipes));
	else if (p2->pid == 0)
		ft_exec_right(t, pipes, sh, p2);
	return (ft_end(t, p1, p2, pipes));
}
