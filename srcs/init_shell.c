/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

t_shell *ft_get_set_shell(t_shell *sh)
{
	static t_shell *s = NULL;

	if (sh != NULL)
	{
		s = sh;
		if (sh->env)
			ft_get_set_envv(sh->env);
	}
	return (s);
}

char *get_shell_path(t_envv *env, char *path)
{
	char *pwd;

	if (*path == '/')
		return (ft_strdup(path));
	else if (ft_str_startwith(path, "./")
	&& (pwd = get_tenvv_val(env, "PWD")))
		return (ft_strjoin(pwd, path + 1));
	return (NULL);
}

char *ft_strchr_end(const char *s, char c)
{
	int i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

void init_shell(t_shell *sh, char **envv, char **argv)
{
	char *shell_path;
	char *shell_fold;
	char *hi_path;
	char *rc_path;
	char *pwd;
	char buff[4097];

	pwd = getcwd(buff, 4096);
	sh->intern = NULL;
	sh->alias = NULL;
	rc_path = NULL;
	sh->env = init_tenvv(envv);
	sh->env = ft_new_envv(sh->env, "PWD", pwd);
	if ((shell_path = ft_strjoin(pwd , (**argv == '.' ? *argv + 1 : *argv ))))
	{
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
				sh = ft_get_set_shell(sh);
				exec_file(rc_path);
				ft_strdel(&rc_path);
			}
			ft_strdel(&shell_fold);
		}
		ft_strdel(&shell_path);
	}
}
