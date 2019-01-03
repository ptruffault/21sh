/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:10:54 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static t_envv	*change_dir(char *path, char *cwd, t_envv *envv)
{
	char	buff[4097];

	if (!chdir(path))
	{
		envv = ft_new_envv(envv, "OLDPWD", cwd);
		envv = ft_new_envv(envv, "PWD", getcwd(buff, 4096));
	}
	else
	{
		if (access(path, F_OK) == -1)
			error("no such file or directory: ", path);
		else if (access(path, R_OK) == -1)
			error("permission denied: ", path);
		else
			error("not a directory: ", path);
	}
	return (envv);
}

t_envv			*ft_cd(char **input, t_envv *envv)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	if (!get_tenvv(envv, "HOME"))
		warning("envvironnement \'$HOME\' var not set", NULL);
	else if (!(input[1]))
		return (change_dir(get_tenvv_val(envv, "HOME"), cwd, envv));
	else if (input[1][0] == '-' && input[1][1] == '\0')
		return (envv = change_dir(get_tenvv_val(envv, "OLDPWD"), cwd, envv));
	else if (input[1])
		return (change_dir(input[1], cwd, envv));
	return (envv);
}
