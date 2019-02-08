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

#include <21sh.h>

static t_tree *ft_end_of_pipe(t_tree *t, int pipes[2], int pid[2])
{
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], 0, 0);
	while (t->o_type == O_PIPE)
		t = t->next;
	return (t);
}

t_tree *exec_pipe(t_tree *t)
{
	int			pipes[2];
	int			pid[2];

	if (pipe(pipes) != 0)
	{
		warning("pipe error", NULL);
		return (t);
	}
	if ((pid[0] = fork()) < 0)
		error("fork filed to create a new process in pipe", t->cmd->word);
	else if (pid[0] == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		t->ret = ft_exec(t);
		ft_free_tree(t);
		exit(0);
	}
	if ((pid[1] = fork()) < 0)
		error("fork filed to create a new process in pipe", t->cmd->word);
	else if (pid[1] == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		exec_instruction(t->next);
		ft_free_tree(t);
		exit(0);
	}
	return (ft_end_of_pipe(t, pipes, pid));
}