/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:54:19 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:54:22 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_del_tfile(t_file *file)
{
	if (file->type == 'l' && (file->link))
		ft_strdel(&file->link);
	if ((file->name))
		ft_strdel(&file->name);
	if ((file->owner))
		ft_strdel(&file->owner);
	if ((file->group))
		ft_strdel(&file->group);
	if ((file->mode))
		ft_strdel(&file->mode);
	if ((file->path))
		ft_strdel(&file->path);
	file->next = NULL;
	file->sdir = NULL;
	free(file);
	file = NULL;
}

void	ft_free_tfile(t_file *file)
{
	t_file *tmp;

	while (file)
	{
		tmp = file->next;
		if (file->type == 'd' && (file->sdir))
			ft_free_tfile(file->sdir);
		ft_del_tfile(file);
		file = tmp;
	}
}
