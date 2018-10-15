/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:40:10 by ptruffau          #+#    #+#             */
/*   Updated: 2018/08/20 14:40:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int		check_void_input(char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (!IS_SPACE(s[i++]))
			return (0);
	return (1);
}

static int	ft_exec(char *path, char **args, t_envv *envv)
{
	pid_t	pid;
	char	**arr;

	arr = tenvv_to_tab(envv);
	if ((pid = fork()) == 0)
	{
		execve(path, args, arr);
	}
	else if (pid < 0)
	{
		error("Fork failed to create a new process", path);
		ft_strdel(&path);
		return (-1);
	}
	ft_freestrarr(arr);
	wait(&pid);
	return (1);
}

void		run_bin(char **args, t_envv *envv)
{
	char *bin_path;

	if ((bin_path = check_bin(args, envv))
	&& (ft_exec(bin_path, args, envv) > 0))
		ft_strdel(&bin_path);
	else if (!bin_path)
		error("command not found", *args);
}

t_envv		*read_cmd(t_envv *envv, char *input, char **arr)
{
	char	**cmd;
	int		inf;

	if (check_void_input(input))
		return (envv);
	else if (!(cmd = ft_correct(ft_strsplit_word(input), envv)))
		return (envv);
	inf = check_builtin(cmd);
	if (inf == 1)
		envv = run_builtin(cmd, envv, arr);
	else if (inf == 0)
		run_bin(cmd, envv);
	ft_freestrarr(cmd);
	return (envv);
}
