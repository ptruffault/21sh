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

int		exec_fd(int fd)
{
	char	**instruct;
	int		i;
	t_tree	*t;

	i = 0;
	if ((instruct = ft_get_txt(fd)))
	{

		while (instruct[i])
		{
			printf("->%s\n",instruct[i] );
			if (*instruct[i] && *instruct[i] != '#'
			&& (t = get_tree(instruct[i])))
				ft_free_tree(exec_tree(ft_get_set_tree(t)));
			i++;
		}
		ft_freestrarr(instruct);
	}
	return (i);
}

void	exec_file(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDWR, S_IRWXU)) >= 0)
	{
		exec_fd(fd);
		ft_close(fd);
	}
	else
		perror(path);
}
