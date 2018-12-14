/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:26:09 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/05 13:26:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static t_tree *next_instruction(t_tree *t)
{
	if (t->o_type && t->next)
	{
		if (t->o_type == O_SEP)
			return (t->next);
		if (t->o_type == O_AND || t->o_type == O_OR)
		{
			unsigned int tmp;

			if ((t->o_type == O_AND && t->ret == 0)
			|| (t->o_type == O_OR && t->ret != 0))
				return (t->next);
			else
			{
				tmp = t->o_type;
				while (t->next && t->o_type == tmp)
				{
					t = t->next;
					if (t->o_type != tmp && t->next)
						return (t);
				}
				return (NULL);
			}
		}
	}
	return (NULL);
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
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[0] == 0)
	{
		dup2(pipes[1], t->fd[STDOUT]);
		close(pipes[0]);
		ft_exec(t);
		ft_free_tree(t);
		exit(0);
	}
	if ((pid[1] = fork()) < 0)
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[1] == 0)
	{
		dup2(pipes[0], t->fd[STDIN]);
		close(pipes[1]);
		t = exec_instruction(t->next);
		ft_free_tree(t);
		exit(0);
	} 
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (t);
}

void ft_exec(t_tree *t)
{
	t_envv *e;

	if (t->r)
		ft_redirect(t);
	if (check_builtin(t->arr))
		run_builtin(t);
	else
	{
		e = ft_get_set_envv(NULL);
		t->ret = ft_execve(t->arr, e);
	}
	reset_fd(t);
}

t_tree *exec_instruction(t_tree *t)
{
	if (t->o_type == O_PIPE)
		return (exec_pipe(t));
	else
		ft_exec(t);
	return (t);
}



void exec_tree(t_tree *t)
{
	t_tree *tmp;

	tmp = t;
	while (tmp)
	{
		printf("in ecex loop\n");
		tmp = exec_instruction(tmp);
		tmp = next_instruction(tmp);
	}
}