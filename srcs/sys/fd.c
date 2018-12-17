/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:19 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

int fd_valid(int fd)
{
	if (isatty(fd) == 0)
	{
		error("Bad file descriptor", NULL);
		return (0);
	}
	return (1);

}

int fd_dup(int fd1, int fd2)
{
	if (fd1 == fd2 || !fd_valid(fd1 || !fd_valid(fd2)))
		return (-1);
	if (dup2(fd1, fd2) < 0)
	{
		warning("can 't duplicate fd", NULL);
		return (-1);
	}
	if (!IS_STD(fd1) && close(fd1) < 0)
	{
		warning("can't close fd", NULL);
		return (-1);
	}
	return (0);
}