/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:54 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:13:55 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char	*check_exe(char *bin_path, struct stat inf)
{
	if (inf.st_mode & S_IFREG)
	{
		if (inf.st_mode & S_IXUSR)
			return (bin_path);
		else
		{
			error("permission denied", bin_path);
			free(bin_path);
		}
		return (NULL);
	}
	else
	{
		error("not an executable", bin_path);
		free(bin_path);
	}
	return (NULL);
}

static char	*local_try(char **input, t_envv *envv)
{
	char		*path;
	struct stat	inf;

	if (lstat(input[0], &inf) == -1)
	{
		path = ft_new_path(get_tenvv_val(envv, "PWD"), input[0]);
		if (lstat(path, &inf) == -1)
		{
			ft_strdel(&path);
			return (NULL);
		}
	}
	else
		path = ft_strdup(input[0]);
	return (check_exe(path, inf));
}

static char	*check_path(char **input, char **path)
{
	int			i;
	char		*bin_path;
	struct stat	inf;

	i = 0;
	while (path[i])
	{
		bin_path = ft_new_path(path[i], input[0]);
		if (lstat(bin_path, &inf) == -1)
			ft_strdel(&bin_path);
		else
		{
			ft_freestrarr(path);
			return (check_exe(bin_path, inf));
		}
		i++;
	}
	ft_freestrarr(path);
	return (NULL);
}

char		*check_bin(char **input, t_envv *envv)
{
	char			*bin_path;
	char			**path;

	path = NULL;
	if ((bin_path = local_try(input, envv)))
		return (bin_path);
	if (!(path = ft_strsplit(get_tenvv_val(envv, "PATH"), ':')))
	{
		warning("PATH might be empty", NULL);
		return (NULL);
	}
	return (check_path(input, path));
}
