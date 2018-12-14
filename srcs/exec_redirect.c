#include <21sh.h>




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



