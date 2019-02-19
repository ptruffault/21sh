/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:08:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/19 14:00:37 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"

static char	*get_shell_path(t_envv *env, char *path)
{
	char *pwd;

	if (*path == '/')
		return (ft_strdup(path));
	else if (ft_str_startwith(path, "./")
	&& (pwd = get_tenvv_val(env, "PWD")))
		return (ft_strjoin(pwd, path + 1));
	return (NULL);
}

static void	ft_update_shelvl(t_shell *sh)
{
	t_envv	*shell_lvl;
	char	*nbr;
	int		lvl;

	if ((shell_lvl = get_tenvv(sh->env, "SHLVL")))
		lvl = ft_atoi(shell_lvl->value);
	else
		lvl = 0;
	nbr = ft_itoa(lvl + 1);
	sh->env = ft_new_envv(sh->env, "SHLVL", nbr);
	ft_strdel(&nbr);
}

static void	init_env(t_shell *sh, char *shell_path, char *pwd)
{
	char *shell_fold;
	char *hi_path;
	char *rc_path;

	sh->env = ft_new_envv(sh->env, "SHELL", shell_path);
	sh->env = ft_new_envv(sh->env, "TERM", "xterm-256color");
	if ((pwd = ft_strchr_end(shell_path, '/'))
	&& (shell_fold = ft_strndup(shell_path, pwd - shell_path)))
	{
		sh->env = ft_new_envv(sh->env, "SHELL_FOLD", shell_fold);
		if ((hi_path = ft_strjoin(shell_fold, "/sys/.21history"))
		&& (sh->env = ft_new_envv(sh->env, "HISTORY", hi_path)))
		{
			sh->hist = init_hist(hi_path);
			ft_strdel(&hi_path);
		}
		ft_update_shelvl(sh);
		if ((rc_path = ft_strjoin(shell_fold, "/sys/.21shrc")))
		{
			exec_file(rc_path);
			ft_strdel(&rc_path);
		}
		ft_strdel(&shell_fold);
	}
}

void		init_shell(t_shell *sh, char **envv, char **argv)
{
	char *shell_path;
	char buff[4097];

	sh->heredoc = 0;
	sh->intern = NULL;
	sh->clipboard = NULL;
	sh->alias = NULL;
	sh->saved_term = NULL;
	sh->process = NULL;
	sh->env = init_tenvv(envv);
	sh->env = ft_new_envv(sh->env, "PWD", getcwd(buff, 4096));
	if (isatty(0) == 0)
	{
		if (exec_fd(0) == 0)
			error("no standart input", NULL);
		ft_free_tenvv(sh->env);
		exit(0);
	}
	init_termcaps(sh);
	if ((shell_path = get_shell_path(sh->env, *argv)))
	{
		init_env(sh, shell_path, getcwd(buff, 4096));
		ft_strdel(&shell_path);
	}
}
