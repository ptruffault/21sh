/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:09:28 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 14:05:10 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int			fd_dup(int fd1, int fd2)
{
	int ret;

	if (fd1 == fd2)
		return (0);
	if ((ret = dup2(fd1, fd2)) < 0)
		return (-1);
	if (!IS_STD(fd1) && ft_close(fd1) == -1)
		return (-1);
	return (ret);
}

static void	ft_heredoc_content(t_redirect *r)
{
	int fd[2];

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

int			get_destination_fd(t_redirect *r)
{
	if ((r->t == R_RIGHT && r->to == -2 &&
	(r->to = open(r->path, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_DRIGHT && r->to == -2 &&
	(r->to = open(r->path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_LEFT && r->to == -2 &&
	(r->to = open(r->path, O_RDONLY, S_IRWXU)) == -1))
	{
		warning("can't open this file", r->path);
		perror(NULL);
		return (-1);
	}
	else if (r->t == R_DLEFT)
		ft_heredoc_content(r);
	if (r->to >= 0 && r->from >= 0)
		return (1);
	return (-1);
}

void		ft_redirect_back(void)
{
	int fd;

	if ((fd = open("/dev/null",
	O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) != -1)
	{
		fd_dup(0, fd);
		fd_dup(1, fd);
		fd_dup(2, fd);
	}
	else
		error("can't open", "/dev/null");
}