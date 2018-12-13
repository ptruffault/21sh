#include <21sh.h>





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


/*int		redirect_dless(t_redir *redir)
{
	int		fds[2];
	char	*str;

	pipe(fds);
	str = redir->heredoc_data;
	write(fds[PIPE_WRITE], str, ft_strlen(str));
	close(fds[PIPE_WRITE]);
	fd_replace(fds[PIPE_READ], redir->n);
	return (0);
}

int		redirect_less(t_redir *redir)
{
	int		fdold;
	int		fdnew;

	fdnew = redir->n;
	if ((try_access(redir->word, 1, R_OK)) != 0)
		return (ft_perror(NULL));
	if ((fdold = open(redir->word, O_RDONLY, 0644)) < 0)
		exit(1);
	fd_replace(fdold, fdnew);
	return (0);
}*/


t_envv *ft_exec_redirection(t_tree *t, t_envv *e, t_redirect *r)
{
	int save[2];

	save[0] = -1;
	save[1] = -1;
	if (r->to < 0)
		get_destination_fd(r);
	if (r->to >= 0 && r->from >= 0)
	{
		if ((0 <= r->from && r->from <= 2 && (save[0] = dup(r->from)) == -1)
		|| (0 <= r->to && r->to <= 2 && (save[1] = dup(r->to)) == -1))
			error("impossible to save file descriptor (dup)", NULL);
		else if (fd_dup(r->to, r->from) == -1)
			warning("redirection failed", NULL);
		if (t->r->next)
			ft_exec_redirection(t, e, r->next);
		else
			e = ft_exec(t, e, NULL);
		if ((0 <= r->from && r->from <= 2 && save[0] != -1 && (close(r->from) == -1 || (r->from = dup(save[0])) == -1 || close(save[0]) == -1))
		|| (0 <= r->to && r->to <= 2 && save[1] != -1 && ((r->to = dup(save[1])) == -1 || close(save[1]) == -1)))
			warning("redirection can't load old fd", NULL);
	}
	return (e);
}


t_envv *exec_pipe(t_tree *t, t_envv *e)
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
		ft_free_tree(t);
		ft_free_tenvv(e);
		exit(0);
	}
	if ((pid[1] = fork()) < 0)
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[1] == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		if (t->next && t->next->r)
			e = ft_exec_redirection(t->next, e, t->next->r);
		else
			e = exec_instruction(t->next, e);
		ft_free_tree(t);
		ft_free_tenvv(e);
		exit(0);
	} 
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (e);
}