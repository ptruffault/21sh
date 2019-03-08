/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:38:45 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/04 12:38:46 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"

static char	*get_shell_path(char *path, char *pwd)
{
	if (*path == '/')
		return (ft_strdup(path));
	if (ft_str_startwith(path, "./") && pwd)
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

static void	ft_setup_env(t_shell *sh, char *shell_fold)
{
	char *hi_path;
	char *rc_path;

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
		exec_file(rc_path, sh);
		ft_strdel(&rc_path);
	}
}

char		*ft_update_pwd(t_shell *sh)
{
	char buff[4097];
	char *pwd;

	pwd = getcwd(buff, 4096);
	sh->env = ft_new_envv(sh->env, "PWD", pwd);
	return (get_tenvv_val(sh->env, "PWD"));
}

void		init_env(t_shell *sh, char **argv)
{
	char *shell_fold;
	char *shell_path;
	char *pwd;

	sh->env = ft_new_envv(sh->env, "TERM", "xterm-256color");
	if ((pwd = ft_strdup(ft_update_pwd(sh))))
	{
		if ((shell_path = get_shell_path(*argv, pwd)))
		{
			sh->env = ft_new_envv(sh->env, "SHELL", shell_path);
			if ((shell_fold = ft_get_prev_path(shell_path)))
			{
				ft_setup_env(sh, shell_fold);
				ft_strdel(&shell_fold);
			}
			ft_strdel(&shell_path);
		}
		ft_strdel(&pwd);
	}
}
