/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:28 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 13:26:00 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int			check_fd(t_process *p, int fd)
{
	if (IS_STD(fd))
	{
		if (p->fd[fd] == -1)
		{
			error_i("bad file descriptor", fd);
			return (-2);
		}
	}
	return (fd);
}

int			fd_dup(int fd1, int fd2, t_process *p, int close)
{
	int ret;

	ret = 0;
	if (fd1 == fd2 || (fd1 = check_fd(p, fd1)) == -2)
		return (-1);
	if (fd1 == -1
	&& (fd1 = open("/dev/null", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU)) < 0)
		warning("can't open this file", "dev/null");
	else
	{
		ret = dup2(fd1, fd2);
		if (close && !IS_STD(fd1))
			ft_close(fd1);
	}
	return (ret);
}

static void	ft_heredoc_content(t_redirect *r, t_shell *sh)
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		ft_free_tshell(sh);
		ft_free_tree(ft_get_set_tree(NULL));
		exit(13);
	}
	else
	{
		ft_putstr_fd(r->heredoc, fd[1]);
		ft_close(fd[1]);
		r->to = fd[0];
		r->from = STDIN_FILENO;
	}
}

int			get_destination_fd(t_redirect *r)
{
	r->path = ft_exp_var(r->path, ft_get_set_shell(NULL));
	if ((r->t == R_RIGHT && r->to == -2 && r->path
	&& (r->to = open(r->path, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_DRIGHT && r->to == -2 && r->path
	&& (r->to = open(r->path, O_RDWR | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_LEFT && r->to == -2 && r->path
	&& (r->to = open(r->path, O_RDWR, S_IRWXU)) == -1))
	{
		warning("can't open this file", r->path);
		perror(NULL);
		return (0);
	}
	else if (r->t == R_DLEFT)
		ft_heredoc_content(r, ft_get_set_shell(NULL));
	if (r->to != -2 && r->from != -2)
		return (1);
	return (0);
}
