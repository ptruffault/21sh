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
					if (!t)
						return (NULL);
				}
				return (t);
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
		exec_instruction(t->next);
		ft_free_tree(t);
		exit(0);
	} 
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (t->next);
}




static void get_destination_fd(t_redirect *r)
{	
	int fd[2];

	if ((r->t == R_RIGHT && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU)) == -1)
	|| (r->t == R_DRIGHT && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_LEFT && r->to == -2 && (r->to = open(r->path, O_RDONLY , S_IRWXU)) == -1))
	{
 		warning("can't open this file", r->path);
		perror(NULL);
	}
	else if (r->t == R_DLEFT && r->heredoc)
	{
		if (pipe(fd) == -1)
			error("pipe error", "heredoc");
		else
		{
			ft_putstr_fd(r->heredoc, fd[1]);
			if (close(fd[1]) == -1)
				warning("can't close", "heredoc");
			r->to = fd[0];
			r->from = STDIN_FILENO;
		}
	}
}



t_tree *ft_exec_redirection(t_tree *t, t_redirect *r)
{
	int save[2];

	save[0] = -1;
	save[1] = -1;
	printf("exec redir\n");
	if (r->to < 0)
		get_destination_fd(r);
	if (r->to >= 0 && r->from >= 0)
	{
		if ((IS_STD(r->from) && (save[0] = dup(r->from)) == -1)
		|| (IS_STD(r->to) && (save[1] = dup(r->to)) == -1))
			error("impossible to save file descriptor (dup)", NULL);
		else if (fd_dup(r->to, r->from) == -1)
			warning("redirection failed", NULL);
		r->done = 1;
		if (IS_STD(r->from))
			t->fd[r->from] = r->to;
		if (t->r->next)
			t = ft_exec_redirection(t, t->r->next);
		else
			 t = exec_instruction(t);
		if ((IS_STD(r->from) && save[0] != -1 && (close(r->from) == -1 || (r->from = dup(save[0])) == -1 || close(save[0]) == -1))
		|| (IS_STD(r->to) && save[1] != -1 && ((r->to = dup(save[1])) == -1 || close(save[1]) == -1)))
			warning("redirection can't load old fd", NULL);
	}
	return (t);
}


void ft_redirect(t_tree *t)
{
	t_redirect *r;

	r = t->r;


	while (r)
	{
		printf("in red loop\n");
		if (r->to < 0)
			get_destination_fd(r);
		if (r->to >= 0 && r->from >= 0)
		{
			printf("from %i to %i\n", r->from, r->to);
			if ((IS_STD(r->from) && (t->fd[r->from] = dup(r->from)) == -1)
			|| (IS_STD(r->to) && (t->fd[r->to] = dup(t->fd[r->to])) == -1))
				error("impossible to save file descriptor (dup)", NULL);
			else if (fd_dup(r->to, r->from) == -1)
				warning("redirection failed", NULL);
		}
		r = r->next;
	}

}


void reset_fd(t_tree *t)
{
	int fd;

	fd = 0;
	while (fd <= 2)
	{
		if (t->fd[fd] != fd)
		{
			printf("reseting fd %i\n", t->fd[fd]);
			if (close(fd) == -1)
				warning("can't close fd 0", NULL);
			if ((fd = dup(t->fd[fd])) == -1)
				error("can't load old fd", NULL);
			if (close(t->fd[fd]) == -1)
				warning("can't close fd 1", NULL);
			t->fd[fd] = fd;
			printf("now %i\n", fd);
		}
		fd++;

	}
}

void ft_exec(t_tree *t)
{
	printf("ft_exec\n");
	if (t->r)
		ft_redirect(t);
	//printf("stdin = %i\nstdout = %i\nstderr = %i\n\n",t->fd[0],t->fd[1],t->fd[2]);
	if (check_builtin(t->arr))
		run_builtin(t);
	else
		t->ret = ft_execve(t->arr);
	reset_fd(t);
	//reset fd
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
		tmp = exec_instruction(tmp);
		tmp = next_instruction(tmp);
	}
}