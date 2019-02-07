#include <21sh.h>

static int get_destination_fd(t_redirect *r)
{	
	int fd[2];

	if ((r->t == R_RIGHT && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU)) == -1)
	|| (r->t == R_DRIGHT && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_LEFT && r->to == -2 && (r->to = open(r->path, O_RDONLY , S_IRWXU)) == -1))
	{
 		warning("can't open this file", r->path);
		perror(NULL);
		return (-1);
	}
	else if (r->t == R_DLEFT && r->heredoc)
	{
		if (pipe(fd) == -1)
			exit(13);
		else
		{
			ft_putstr_fd(r->heredoc, fd[1]);
			ft_close(fd[1]);
			r->to = fd[0];
			r->from = STDIN_FILENO;
		}
	}
	if (r->to >= 0 && r->from >= 0)
		return (1);
	else
		return (-1);
}

int fd_dup(int fd1, int fd2, int close)
{
	if (fd1 == fd2)
		return (0);
	if (dup2(fd1, fd2) < 0)
		return (-1);
	if ((close || !IS_STD(fd1)) && ft_close(fd1) == -1)
		return (-1);
	return (0);
}

int ft_redirect(t_tree *t)
{
	t_redirect *r;
	int  fd;

	r = t->r;
	if (t->o_type == O_BACK)
	{
		if ((fd = open("/dev/null", O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) != -1)
		{
			fd_dup(0, fd, 1);
			fd_dup(1, fd, 1);
			fd_dup(2, fd, 1);
		}
		else
			error("can't open", "/dev/null");
	}
	while (r)
	{
		if (get_destination_fd(r) < 0 || fd_dup(r->to, r->from, 0) == -1)
		{
			error("redirection failed", NULL);
			exit(-1);
		}
		r = r->next;
	}
	return (0);
}

int ft_redirect_builtin(t_tree *t, int fd[3])
{
	t_redirect *r;

	r = t->r;
	while (r)
	{
		if (get_destination_fd(r) < 0)
			return (-1);
		if (IS_STD(r->from))
			fd[r->from] = dup(r->from);
		if (fd_dup(r->to, r->from, 0) == -1)
		{
			error("redirection failed", NULL);
			return (-1);
		}
		r = r->next;
	}
	return (0);
}

void ft_reset_fd(int fd[3])
{
	int i;
	int tmp;

	i = 0;
	while (i <= 2)
	{
		if (fd[i] != i)
		{
			ft_close(i);
			if ((tmp = dup(fd[i])) == -1)
				error("can't load old fd", NULL);
			ft_close(fd[i]);
			fd[i] = tmp;
		}
		i++;

	}
}


