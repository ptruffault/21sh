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
	char *rc_path;
	t_tree *t;
	char **instruct;
	int i;
	(void)argv;

	sh->intern = NULL;
	sh->alias = NULL;
	rc_path = NULL;
	instruct = NULL;
	i = 0;
	sh = ft_get_set_shell(sh);
	if ((sh->env = ft_get_set_envv(init_tenvv(envv)))
	&& (rc_path = ft_strjoin(get_tenvv_val(sh->env, "HOME"), "/.21shrc"))
	&& (instruct = ft_get_txt(open(rc_path, S_IRWXU , O_RDWR))))
	{
		while (instruct && instruct[i])
		{
			if ((t = ft_get_set_tree(get_tree(instruct[i++]))))
			{
				exec_tree(t);
				ft_free_tree(t);
			}
		}
	}
	free(instruct);
	ft_strdel(&rc_path);
	ft_get_set_shell(sh);
}
