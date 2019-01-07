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

static char	*absolute_path(char *input, t_envv *envv)
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

char	*get_bin_path(char *input, t_envv *envv)
{
	int			i;
	char		*bin_path;
	struct stat	inf;
	char 		**path;

	i = 0;
	if ((bin_path = absolute_path(input, envv)))
		return (bin_path);
	if (ft_str_startwith(input, "./") || ft_str_startwith(input, "/"))
	{
		error("no such file or directory", input);
		return (NULL);
	}
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
	error("command not found", input);
	return (NULL);
}

int ft_execve(t_tree *t)
{
	t_envv *e;
	int ret;
	char **env;
	char **argv;
	char *bin_path;
	pid_t pid;

	ret = -1;
	if (!(argv = ft_twordto_arr(t->cmd)))
		return (-1);
	if (check_builtin(argv))
		return (run_builtin(t, argv));
	e = ft_get_set_envv(NULL);
	if (!(bin_path = get_bin_path(*argv, e)))
		return (-1);
	env = tenvv_to_tab(e);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", bin_path);
	else if (pid == 0)
	{
		if (t->r && ft_redirect(t) != 0)
			exit(-1);
		else if (execve(bin_path, argv, env) == -1)
			warning("execve fucked up", bin_path);
	}
	else
		wait(&ret);
	ft_freestrarr(env);
	ft_strdel(&bin_path);
	return (ret);
}