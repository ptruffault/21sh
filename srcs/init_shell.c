/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:08:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 12:08:42 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

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

static void	init_env(t_shell *sh, char *shell_path, char *pwd)
{
	char *shell_fold;
	char *hi_path;
	char *rc_path;

	sh->env = ft_new_envv(sh->env, "SHELL", shell_path);
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
	char *pwd;
	char buff[4097];

	pwd = getcwd(buff, 4096);
	sh->intern = NULL;
	sh->alias = NULL;
	sh->process = NULL;
	sh->env = init_tenvv(envv);
	sh->env = ft_new_envv(sh->env, "PWD", pwd);
	if ((shell_path = ft_strjoin(pwd, (**argv == '.' ? *argv + 1 : *argv))))
	{
		init_env(sh, shell_path, pwd);
		ft_strdel(&shell_path);
	}
	init_termcaps(sh);
}
