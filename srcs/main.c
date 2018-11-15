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

pid_t ft_exec_pid(t_tree *t, t_envv *envv)
{
	char **e;
	pid_t pid;

	e = tenvv_to_tab(envv);
	if ((pid = fork()) == 0 && execve(t->arr[0], t->arr, e) == -1)
			warning("execve fucked up", *t->arr);
	 ft_freestrarr(e);
	 return (pid);
}


static t_envv	*ft_exec(t_tree *t, t_envv *envv)
{
	pid_t	pid;

	if (check_builtin(t->arr))
		return (envv = run_builtin(t , envv));
	 if ((pid = ft_exec_pid(t, envv)) != -1)
		wait(&pid);
	else
		error("Fork failed to create a new process", *t->arr);
	return (envv);
}

static void get_destination_fd(t_tree *t)
{	
	if (t->r.to == -2 && ((t->r.t == R && (t->r.to = open(t->r.path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU)) == -1)
	|| (t->r.t == DR && (t->r.to = open(t->r.path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)))
		warning("can't open/create this file", t->r.path);
	else if (t->r.to < 0 && (t->r.to = open("/dev/null", O_WRONLY | O_CREAT, S_IRWXU)) == -1)
		warning("can't write in /dev/null file", NULL);
}

static t_envv *ft_exec_redirection(t_tree *t, t_envv *e)
{
	int save;

	save = 0;

	if (t->r.to < 0)
		get_destination_fd(t);
	if (t->r.to >= 0)
	{
		if ((save = dup(t->r.from)) == -1)
			error("impossible to save file descriptor (dup)", "from");
		else if (dup2(t->r.to, t->r.from) == -1)
			warning("dup2 failed", NULL);
		else if (close(t->r.to) == -1)
			warning("close failed", NULL);
		{
			ft_strdel(&t->r.s);
			e = ft_exec(t, e);
			if (close(t->r.from) == -1)
				warning("can't close", NULL);
			if ((t->r.from = dup(save)) == -1)
				warning("impossible to load old fd", "from_save");
		}
	}
	return (e);
}


static t_envv *ft_exec_pipe(t_tree *t, t_envv *e)
{
	int			pipes[2];
	int			pid[2];


	if (pipe(pipes) != 0)
	{
		warning("pipe error", NULL);
		return (e);
	}
	else if ((pid[0] = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		e = ft_exec(t, e);
		exit(0);
	}
	if ((pid[1] = fork()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		e = ft_exec(t->next, e);
		exit(0);
	} 
	close(pipes[0]);
	close(pipes[1]);
	return (e);
}


t_envv *exec_instruction(t_tree *t, t_envv *e)
{
	if (t->arr)
	{
		if (t->l == '|' && t->next->arr)
		{
			t->l = '.';
			e = ft_exec_pipe(t, e);
		}
		else if (t->r.s && t->l != '.')
			e = ft_exec_redirection(t, e);
		else if (t->arr)
			ft_exec(t, e);
	}
	if (t->l && t->next->arr)
		e = exec_instruction(t->next, e);
	return (e);
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
			my_envv = exec_instruction(t, my_envv);
			ft_free_tree(t);
		}
	}
	return (0);
}