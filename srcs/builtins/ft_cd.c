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

#include "../../includes/shell42.h"

t_envv		*change_dir(char *path, t_envv *envv)
{
	char	buff[4097];
	char	*cwd;

	cwd = getcwd(buff, 4096);
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

t_envv		*ft_cd(char **input, t_envv *envv)
{
	if (!(input[1]))
		if (get_tenvv_val(envv, "HOME"))
			return (change_dir(get_tenvv_val(envv, "HOME"), envv));
		else
			error("UNSET VAR", "HOME");
	else if (input[1][0] == '-' && input[1][1] == '\0')
		if (get_tenvv_val(envv, "HOME"))
			return (change_dir(get_tenvv_val(envv, "OLDPWD"), envv));
		else
			error("UNSET VAR", "OLDPWD");
	else if (input[1])
		return (change_dir(input[1], envv));
	return (envv);
}
