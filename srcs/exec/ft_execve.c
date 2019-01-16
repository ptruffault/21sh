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

int ft_execve(t_redirect *r, char **argv)
{
	t_envv *envv;
	int ret;
	char **env;
	char *bin_path;
	pid_t pid;

	ret = -1;
	envv = ft_get_set_envv(NULL);
	if (!(bin_path = get_bin_path(*argv, envv)))
		return (ret);
	env = tenvv_to_tab(envv);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", bin_path);
	else if (pid == 0)
	{
		ft_redirect(r);
		if (execve(bin_path, argv, env) == -1)
			warning("execve fucked up", bin_path);
	}
	else
	{
		ft_freestrarr(env);
		ft_strdel(&bin_path);
		wait(&ret);
	}
	return (ret);
}

int ft_exec(t_tree *t)
{
	int ret;
	char **argv;

	ret = -1;
	if ((argv = ft_twordto_arr(t->cmd)))
	{
		if (check_builtin(*argv))
			ret = run_builtin(t, argv);
		else
			ret = ft_execve(t->r, argv);
		ft_freestrarr(argv);
	}
	return (ret);
}
