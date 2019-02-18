/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 13:53:24 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static t_tree	*ft_end_of_pipe(t_tree *t, int pipes[2], int pid[2])
{
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], 0, 0);
	while (t->o_type == O_PIPE)
		t = t->next;
	return (t);
}


static void		ft_exec_next(t_tree *t, int pipes[2])
{
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[1]);
	exec_instruction(t);
	exit(0);
}

t_tree			*exec_pipe(t_tree *t)
{
	int			pipes[2];
	int			pid[2];
	t_process	*p;
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (pipe(pipes) != 0 || !(p = init_process(t, sh)))
		return (t);
	if ((pid[0] = fork()) < 0)
		error("fork filed to create a new process in pipe", t->cmd->word);
	else if (pid[0] == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		ft_exec(t, p);
		ft_free_tshell(sh);
		ft_free_tree(t);
		exit(0);
	}
	if ((pid[1] = fork()) < 0)
		error("fork filed to create a new process in pipe", t->cmd->word);
	else if (pid[1] == 0)
		ft_exec_next(t->next, pipes);
	return (ft_end_of_pipe(t, pipes, pid));
}
