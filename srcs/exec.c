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

static void get_destination_fd(t_redirect *r)
{	
	if ((r->t == 0 && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU)) == -1)
	|| (r->t == 1 && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == 2 && r->from == -1 && (r->from = open(r->path, O_WRONLY , S_IRWXU)) == -1))
	{
 		warning("can't open this file", r->path);
		perror(NULL);
	}
	else if (r->to < 0 && (r->to = open("/dev/null", O_WRONLY | O_CREAT, S_IRWXU)) == -1)
		warning("can't write in /dev/null file", NULL);
}

static t_envv *ft_exec_redirection(t_tree *t, t_envv *e, t_redirect *r)
{
	int save[2];

	if (r->to < 0 || r->from < 0)
		get_destination_fd(r);
	if (r->to >= 0 && (r->t == 0 || r->t == 1))
	{
		if (r->to == STDOUT_FILENO && (save[1] = dup(STDOUT_FILENO)) == -1)
			warning("impossible to save STDOUT_FILENO", NULL);
		if ((save[0] = dup(r->from)) == -1)
			error("impossible to save file descriptor (dup)", "from");
		else if (dup2(r->to, r->from) == -1)
			warning("dup2 failed", NULL);
		else if (close(r->to) == -1)
			warning("close failed", NULL);
		{
			e = ft_exec(t, e, r->next);
			if (close(r->from) == -1)
			{
				put_redirect(r);
				warning("redirection can't close", "from");
			}
			if ((r->from = dup(save[0])) == -1)
				warning("impossible to load old fd", NULL);
		}
	}
	return (e);
}

t_envv *ft_exec(t_tree *t, t_envv *envv, t_redirect *r)
{
	char **e;
	pid_t pid;

	if (r)
		return(ft_exec_redirection(t, envv, r));
	if (check_builtin(t->arr))
		return (run_builtin(t, envv));
	e = tenvv_to_tab(envv);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", *t->arr);
	if (pid == 0 && execve(*t->arr, t->arr, e) == -1)
		warning("execve fucked up", *t->arr);
	ft_freestrarr(e);
	wait(&t->ret);
	printf("%i\n",t->ret );
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
		e = ft_exec(t, e, t->r);
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
			e = ft_exec(t, e, t->r);
	}
	if (t->l == ';' && t->next->arr)
		return (exec_instruction(t->next, e));
	return (e);
}