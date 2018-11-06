/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"


static int	ft_exec(char **args, char **envv)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
		execve(args[0], args, envv);
	else if (pid < 0)
	{
		error("Fork failed to create a new process", *args);
		return (-1);
	}
	wait(&pid);
	return (1);
}

static int ft_exec_pipe(t_tree *t, char **envv)
{
	int			pipes[2];
	int			pid[2];

	if (pipe(pipes) != 0)
		ft_putendl_fd("pipe error", 2);
	else if ((pid[0] = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		ft_exec(t->arr, envv);
		exit(0);
	}
	if ((pid[1] = fork()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		exec_instruction(t->next, envv);
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (0);
}

void exec_instruction(t_tree *t, char **envv)
{

	if (t->arr)
	{
		 if (t->l == '|')
		{
			if (t->next->arr)
				ft_exec_pipe(t, envv);
		}
		else
			ft_exec(t->arr, envv);
	}
	if (t->l == ';')
		exec_instruction(t->next, envv);
}

int		main(int argc, char **argv, char **envv)
{
	t_envv	*my_envv;
	t_tree	*t;

	if (!(my_envv = new_tenvv()))
		return (-1);
	my_envv = init_tenvv(my_envv, envv);
	while (42)
	{
		ft_disp(my_envv, argc, argv);
		if ((t = get_tree(get_input(envv), my_envv)))
		{
			exec_instruction(t, envv);
			ft_free_tree(t);
		}
	}
	return (0);
}