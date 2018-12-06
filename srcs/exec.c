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

#include "../includes/21sh.h"

static void get_destination_fd(t_tree *t)
{	
	if ((t->r->t == 0 && t->r->to == -2 && (t->r->to = open(t->r->path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU)) == -1)
	|| (t->r->t == 1 && t->r->to == -2 && (t->r->to = open(t->r->path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (t->r->t == 2 && t->r->from == -1 && (t->r->from = open(t->r->path, O_WRONLY , S_IRWXU)) == -1))
	{
 		warning("can't open this file", t->r->path);
		perror(NULL);
	}
	else if (t->r->to < 0 && (t->r->to = open("/dev/null", O_WRONLY | O_CREAT, S_IRWXU)) == -1)
		warning("can't write in /dev/null file", NULL);
}
static t_envv *ft_exec_redirection(t_tree *t, t_envv *e)
{
	int save;

	save = 0;

	printf("exec redirection\n");
	if (t->r->to < 0 || t->r->from < 0)
		get_destination_fd(t);
	if (t->r->to >= 0 && (t->r->t == 0 || t->r->t == 1)) // HERE I HAVE TO GERER LES REDIRECTION < <<
	{
		if ((save = dup(t->r->from)) == -1)
			error("impossible to save file descriptor (dup)", "from");
		else if (dup2(t->r->to, t->r->from) == -1)
			warning("dup2 failed", NULL);
		else if (close(t->r->to) == -1)
			warning("close failed", NULL);
		{
			printf("HERE I AM\n");
			t->r = t->r->next;
			e = exec_instruction(t, e);
			if (close(t->r->from) == -1)
				warning("can't close", NULL);
			if ((t->r->from = dup(save)) == -1)
				warning("impossible to load old fd", "from_save");
		}
	}
	return (e);
}

t_envv *ft_exec(t_tree *t, t_envv *envv)
{
	char **e;
	int pid;
	int status;

	if (t->r)
		return (ft_exec_redirection(t, envv));
	if (check_builtin(t->arr))
		return (run_builtin(t, envv));
	e = tenvv_to_tab(envv);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", *t->arr);
	if (pid == 0 && execve(*t->arr, t->arr, e) == -1)
		warning("execve fucked up", *t->arr);
	ft_freestrarr(e);
	wait(&status);

	return (envv);
}

static t_envv *exec_pipe(t_tree *t, t_envv *e)
{
	int			pipes[2];
	int			pid[2];

	if (pipe(pipes) != 0)
	{
		warning("pipe error", NULL);
		return (e);
	}
	if ((pid[0] = fork()) < 0)
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[0] == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		e = ft_exec(t, e);
		exit(0);
	}
	if ((pid[1] = fork()) < 0)
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[1] == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
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
			e = exec_pipe(t, e);
		else 
			e = ft_exec(t, e);
	}
	if (t->l == ';' && t->next->arr)
		return (exec_instruction(t->next, e));
	return (e);
}