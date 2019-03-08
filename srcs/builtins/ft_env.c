/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:04:08 by ptruffau          #+#    #+#             */
/*   Updated: 2018/08/20 15:04:10 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static void		ft_env_exec(char **arr, t_envv *tmp, t_envv *envv)
{
	char	**e;
	char	*path;
	int		pid;

	if (!(path = get_bin_path(*arr, envv)))
		return ;
	e = tenvv_to_tab(tmp);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", *arr);
	if (pid == 0)
	{
		execve(path, arr, e);
		warning("{env} execve fucked up", *arr);
	}
	ft_strdel(&path);
	ft_freestrarr(e);
	wait(&pid);
}

static t_envv	*ft_tmpsetenv(t_envv *tmp, char *equal)
{
	t_envv	*ret;
	char	*n;
	char	*v;

	ret = NULL;
	if (!(n = get_name(equal))
	|| !(v = get_value(equal))
	|| !(ret = ft_new_envv(tmp, n, v)))
		warning("impossible to create tmp envv value", NULL);
	ft_strdel(&n);
	ft_strdel(&v);
	return (ret);
}

static t_envv	*init(int *i, t_envv *envv)
{
	t_envv *tmp;

	*i = 1;
	if (!(tmp = ft_tenvv_cpy(envv)))
	{
		error("impossible to create a tempory env", NULL);
		return (NULL);
	}
	return (tmp);
}

static t_envv	*ft_env_option(t_envv *tmp, char **input, int *i)
{
	if (input[*i][1] != 'i' && input[*i][1] != 'u')
		warning_c("invalid option :", input[*i][1]);
	else if (input[*i][1] == 'u')
	{
		if (!input[*i + 1])
		{
			warning("option need an argument", "-u");
			return (tmp);
		}
		if (!tmp)
		{
			warning("useless -u option", "void environement");
			return (tmp);
		}
		*i = *i + 1;
		tmp = ft_del_envv(tmp, input[*i]);
	}
	else if (input[*i][1] == 'i')
	{
		ft_free_tenvv(tmp);
		tmp = NULL;
	}
	return (tmp);
}

int				ft_env(t_envv *envv, char **argv)
{
	t_envv	*tmp;
	int		i;

	if (!(tmp = init(&i, envv)))
		return (-1);
	while (argv[i])
	{
		if (argv[i][0] == '-')
			tmp = ft_env_option(tmp, argv, &i);
		else if (ft_isequal(argv[i]))
			tmp = ft_tmpsetenv(tmp, argv[i]);
		else
		{
			ft_env_exec(&argv[i], tmp, envv);
			ft_free_tenvv(tmp);
			return (0);
		}
		i++;
	}
	ft_puttenvv(tmp);
	ft_free_tenvv(tmp);
	return (0);
}
