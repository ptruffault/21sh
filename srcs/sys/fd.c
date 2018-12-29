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

int fd_dup(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
	{
		error("can 't duplicate fd", NULL);
		return (-1);
	}
	if (close(fd1) == -1)
		warning("can't close file descriptor", NULL);
	return (0);
}