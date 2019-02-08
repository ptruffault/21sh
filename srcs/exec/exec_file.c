/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:59:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 13:59:49 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void	exec_file(char *path)
{
	char	**instruct;
	int		fd;
	int		i;
	t_tree	*t;

	i = 0;
	if ((fd = open(path, O_RDWR, S_IRWXU)) >= 0)
	{
		if ((instruct = ft_get_txt(fd)))
		{
			while (instruct[i])
			{
				if (*instruct[i] && *instruct[i] != '#'
				&& (t = get_tree(instruct[i])))
					ft_free_tree(exec_tree(ft_get_set_tree(t)));
				i++;
			}
			ft_freestrarr(instruct);
		}
		ft_close(fd);
	}
	else
		perror(path);
}
