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

#include "../includes/21sh.h"

static t_envv	*ft_tmpsetenv(t_envv *tmp, char *equal)
{
	t_envv	*ret;
	char	*n;
	char	*v;

	ret = NULL;
	if (!(n = get_name(equal)) ||
	!(v = get_value(equal)) ||
	!(ret = ft_setenv(tmp, n, v)))
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
			error("option need an argument", "-u");
			return (NULL);
		}
		if (!tmp)
		{
			error("useless -u option", "void environement");
			return (NULL);
		}
		*i = *i + 1;
		tmp = ft_unsetenv(tmp, input[*i]);
	}
	else if (input[*i][1] == 'i')
	{
		ft_free_tenvv(tmp);
		tmp = NULL;
	}
	return (tmp);
}

void			ft_env(char **input, t_envv *envv)
{
	t_envv	*tmp;
	int		i;

	tmp = init(&i, envv);
	while (input[i])
	{
		if (input[i][0] == '-')
			tmp = ft_env_option(tmp, input, &i);
		else if (ft_strchr(input[i], '='))
			tmp = ft_tmpsetenv(tmp, input[i]);
		else
		{
			run_bin(&input[i], tmp);
			ft_free_tenvv(tmp);
			return ;
		}
		i++;
	}
	ft_puttenvv(tmp);
	ft_free_tenvv(tmp);
}
