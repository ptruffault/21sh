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

t_process *ft_execve(t_tree *t, char **argv, t_shell *sh)
{
	char **env;
	char *bin_path;
	t_process *new;
	pid_t pid;

	if (!(bin_path = get_bin_path(*argv, sh->env)))
		return (NULL);
	new = NULL;
	env = tenvv_to_tab(sh->env);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", bin_path);
	else if (pid == 0)
	{
		ft_redirect(t);
		if (execve(bin_path, argv, env) == -1)
			warning("execve fucked up", bin_path);
	}
	else
	{
		new = new_process(pid, bin_path, t);
		ft_freestrarr(env);
		ft_strdel(&bin_path);
	}
	return (new);
}

int ft_exec(t_tree *t)
{
	int ret;
	char **argv;
	t_shell *sh;

	ret = -1;
	sh = ft_get_set_shell(NULL);
	if ((argv = ft_twordto_arr(t->cmd)))
	{
		if (check_builtin(*argv))
			ret = run_builtin(t, argv);
		else
		{
			ft_add_process(sh, ft_execve(t, argv, sh));
			if (sh->process->status == RUNNING_FG)
				wait(&sh->process->ret);
		}
		ft_freestrarr(argv);
	}
	return (ret);
}
