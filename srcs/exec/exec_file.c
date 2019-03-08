/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:59:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:49:57 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int		exec_fd(t_shell *sh, int fd)
{
	int		i;
	t_tree	*t;

	i = 0;
	if ((sh->txt = ft_get_txt(fd)))
	{
		while (sh->txt[i])
		{
			if (*sh->txt[i] && *sh->txt[i] != '#'
			&& (t = get_tree(sh->txt[i])))
				ft_free_tree(exec_tree(t));
			i++;
		}
		ft_freestrarr(sh->txt);
	}
	return (i);
}

int		exec_file(char *path, t_shell *sh)
{
	int		fd;

	if ((fd = open(path, O_RDWR, S_IRWXU)) >= 0)
	{
		exec_fd(sh, fd);
		ft_close(fd);
	}
	else
	{
		error("can't exec this file", path);
		return (-1);
	}
	return (0);
}
