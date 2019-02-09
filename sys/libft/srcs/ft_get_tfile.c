/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:16:51 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 17:24:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	read_all_dir(t_file *f, char *path, DIR *dir, int recursive)
{
	struct dirent *t_dir;

	while ((t_dir = readdir(dir)))
	{
		f->next = ft_new_tfile();
		f = f->next;
		ft_get_file_inf(f, t_dir, path);
		if (recursive != 0 && f->type == 'd' &&
		ft_strcmp(f->name, ".") != 0 && ft_strcmp(f->name, "..") != 0)
			f->sdir = ft_get_tfile(f->path, recursive);
	}
}

t_file		*ft_get_tfile(char *path, int recursive)
{
	t_file	*file;
	t_file	*tmp;
	DIR		*dir;

	file = ft_new_tfile();
	if (!(dir = opendir(path)))
	{
		ft_putstr("\033[00;31m\033[04mError:\033[00m");
		perror(path);
		return (NULL);
	}
	else if ((path))
		read_all_dir(file, path, dir, recursive);
	tmp = file->next;
	free(file);
	file = tmp;
	if (closedir(dir) == -1)
		perror(path);
	return (file);
}
