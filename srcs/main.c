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

int ft_exec(t_tree *t, t_envv *envv)
{
	char **e;
	int pid;

	e = tenvv_to_tab(envv);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", *t->arr);
	else if (pid == 0 && (t->ret = execve(*t->arr, t->arr, e) == -1))
		warning("execve fucked up", *t->arr);	
	ft_freestrarr(e);
	wait(&pid);
	return (pid);
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
			t->ret = ft_exec(t, e);
			if (close(t->r.from) == -1)
				warning("can't close", NULL);
			if ((t->r.from = dup(save)) == -1)
				warning("impossible to load old fd", "from_save");
		}
	}
	return (e);
}


/*
    if (argc != 3) usage();
    int pd[2]; //Pipe descriptor
    pipe(pd);
    int pid = fork();
    if (pid < 0) 
    	perror("Something failed on trying to create a child process!\n");
    else if (pid == 0) { //Child
    dup2(pd[0], 0); 
    close(pd[0]);
    close(pd[1]);
    execlp("wc", "wc", "-l", (char *)NULL);
    fprintf(stderr, "Failed to execute 'wc'\n");
    exit(1);
	}
    else { //Parent
        dup2(pd[0], 1);
        close(pd[0]);
        close(pd[1]);
        execlp("grep", "grep", argv[1], argv[2], (char *)NULL);
    }
}
*/

static t_envv *ft_exec_pipe(t_tree *t, t_envv *e)
{
	int			pipes[2];
	int			pid[2];

	if (pipe(pipes) != 0)
	{
		warning("pipe error", NULL);
		return (e);
	}
	if ((pid[0] = fork()) == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		if (close(pipes[0] == -1))
			warning("cant close", "pipe[0] || STDOUT");
		e = exec_instruction(t, e);
		exit(0);
	}
	if ((pid[1] = fork()) == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		if (close(pipes[1] == -1))
			warning("cant close", "pipe[1]");
		e = exec_instruction(t->next, e);
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0); 
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
		else if (check_builtin(t->arr))
			e = run_builtin(t , e);
		else if ((t->ret = ft_exec(t, e)) == -1)
			warning("-1 value returned by ft_exec", *t->arr);
	}
	if (t->l == ';' && t->next->arr)
		return (exec_instruction(t->next, e));
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