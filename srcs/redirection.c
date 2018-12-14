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

void ft_redirect(t_tree *t)
{
	t_redirect *r;

	r = t->r;


	while (r)
	{
		if (r->to < 0)
			get_destination_fd(r);
		if (r->to >= 0 && r->from >= 0)
		{
			printf("redirect\n");
			if ((IS_STD(r->from) && (t->fd[r->from] = dup(r->from)) == -1)
			|| (IS_STD(r->to) && (t->fd[r->to] = dup(t->fd[r->to])) == -1))
				error("impossible to save file descriptor (dup)", NULL);
			else if (fd_dup(r->to, r->from) == -1)
				warning("redirection failed", NULL);
		}
		printf("here i am\n");
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
			if (close(fd) == -1)
				warning("can't close fd 0", NULL);
			if ((fd = dup(t->fd[fd])) == -1)
				error("can't load old fd", NULL);
			if (close(t->fd[fd]) == -1)
				warning("can't close fd 1", NULL);
			t->fd[fd] = fd;
		}
		fd++;

	}
}
