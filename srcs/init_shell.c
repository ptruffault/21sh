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
		s = sh;
	return (s);
}


t_envv *init_envvironnment(char **envv)
{
	t_shell sh;


	t_envv *new;
	t_envv *tmp;

	if (!(new = ft_init_tenvv_file("/home/ptruffau/21sh/sys/env")))
		return (NULL);
	if (!(sh.env  = init_tenvv(envv)))
		return (NULL);
	tmp = new;
	while (tmp)
	{
		tmp->value = ft_exp_var(tmp->value, &sh);
		tmp = tmp->next;
	}
	ft_free_tenvv(sh.env);
	return (new);

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

void init_shell(t_shell *sh,char **argv, char **envv)
{
	char *shell_path;
	char *sys_path;

	sh->intern = NULL;
	if (!(ft_get_set_envv(sh->env = init_envvironnment(envv))))
		warning("void environnement", NULL);
	if ((shell_path = get_shell_path(sh->env, argv[0])))
	{
		sh->env = ft_new_envv(sh->env, "SHELL", shell_path);
		if ((sys_path = ft_strjoin_fr(ft_get_prev_path(shell_path), ft_strdup("/sys"))))
		{
			sh->env = ft_new_envv(sh->env, "SYS", sys_path);
			ft_strdel(&sys_path);
		}
		ft_strdel(&shell_path);
	}
	sh->alias = ft_init_tenvv_file("/home/ptruffau/21sh/sys/alias");
	ft_get_set_shell(sh);
}
