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
		set_prgm_signal();
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
