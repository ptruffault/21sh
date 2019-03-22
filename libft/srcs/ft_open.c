/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:28:15 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/19 11:37:45 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_open(char *path, int flag, mode_t mode)
{
	int fd;
	struct stat	inf;

	fd = -1;
	if (!(flag & O_CREAT) && lstat(path, &inf) == -1)
		error("no such file or directory", path);
	else if (!(flag & O_CREAT) && S_ISDIR(inf.st_mode))
		error("is a directory", path);
	else if (!(flag & O_CREAT) && !(inf.st_mode & S_IRUSR))
		error("permission denied", path);
	else if (!(flag & O_CREAT) && S_ISLNK(inf.st_mode))
		error("ft_open do not follow symbolic link", path);
	else if ((fd = open(path, flag, mode)) < 0)
		error("can't open this file", path);
	return (fd);
}
