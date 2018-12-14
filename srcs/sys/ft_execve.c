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

int ft_execve(char **argv)
{
	t_envv *e;
	int ret;
	char **env;
	char *bin_path;
	pid_t pid;

	e = ft_get_set_envv(NULL);
	if (!(bin_path = get_bin_path(*argv, e)))
	{
		error("unknow cmd", *argv);
		return (-1);
	}
	env = tenvv_to_tab(e);
	if ((pid = fork()) == -1)
	{
		warning("fork failed to create a new process", bin_path);
		return (-1);
	}
	if (pid == 0 && execve(bin_path, argv, env) == -1)
	{
		warning("execve fucked up", bin_path);
		return (-1);
	}
	ft_freestrarr(env);
	ft_strdel(&bin_path);
	wait(&ret);
	return (ret);
}