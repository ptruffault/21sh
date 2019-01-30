/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:19 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static char	*check_exe(char *bin_path, struct stat inf)
{
	if (inf.st_mode & S_IFREG)
	{
		if (inf.st_mode & S_IXUSR)
			return (bin_path);
		else
			error("permission denied", bin_path);
	}
	else
		error("not an executable", bin_path);
	ft_strdel(&bin_path);
	return (NULL);
}

char	*absolute_path(char *input, t_envv *envv)
{
	char		*path;
	struct stat	inf;

	if (lstat(input, &inf) == -1)
	{
		path = ft_new_path(get_tenvv_val(envv, "PWD"), input);
		if (lstat(path, &inf) == -1)
		{
			ft_strdel(&path);
			return (NULL);
		}
	}
	else
		path = ft_strdup(input);
	return (check_exe(path, inf));
}

char *search_in_envv(char *input, t_envv *envv)
{
	char *bin_path;
	char **path;
	struct stat	inf;
	int i;

	i = 0;
	if (!(path = ft_strsplit(get_tenvv_val(envv, "PATH"), ':')))
		return (NULL);
	while (path[i])
	{
		bin_path = ft_new_path(path[i], input);
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


char	*get_bin_path(char *input, t_envv *envv)
{
	char		*bin_path;

	if (ft_str_startwith(input, "./") || ft_str_startwith(input, "/"))
	{ 
		if ((bin_path = absolute_path(input, envv)))
			return (bin_path);
		error("no such file or directory", input);
		return (NULL);
	}
	if (!(bin_path = search_in_envv(input, envv)))
		error("command not found", input);
	return (bin_path);
}
