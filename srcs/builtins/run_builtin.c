/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:13:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int		check_arg(char **input, int n)
{
	int i;

	if (input[n] && !(input[n + 1]))
		return (1);
	else
	{
		ft_putstr_fd("\033[00;31mUsage : \033[00m", 2);
		ft_putstr_fd(input[0], 2);
		i = 0;
		if (n == 0)
			ft_putstr_fd("\t\033[04m (void) \033[00m", 2);
		while (i++ < n)
			ft_putstr_fd("\t\033[04m [arg] \033[00m", 2);
		ft_putchar('\n');
	}
	return (-1);
}

int				check_builtin(char **input)
{
	if (!input[0])
		return (1);
	if (ft_strequ(input[0], "env"))
		return (1);
	else if (ft_strequ(input[0], "exit"))
		return (check_arg(input, 0));
	else if (ft_strequ(input[0], "pwd"))
		return (check_arg(input, 0));
	else if (ft_strequ(input[0], "unsetenv") || ft_strequ(input[0], "unset"))
		return (check_arg(input, 1));
	else if (ft_strequ(input[0], "setenv") || ft_strequ(input[0], "export"))
		return (check_arg(input, 2));
	else if (ft_strequ(input[0], "cd"))
		return (1);
	else if (ft_strequ(input[0], "echo"))
		return (1);
	else
		return (0);
}

static t_envv	*change_envv(char **input, t_envv *envv)
{
	if (ft_strequ(input[0], "unsetenv") || ft_strequ(input[0], "unset"))
		return (ft_unsetenv(envv, input[1]));
	else if ((ft_strequ(input[0], "setenv") || ft_strequ(input[0], "export")) &&
	(!(envv = ft_setenv(envv, input[1], input[2]))))
	{
		error("impossible to create", input[1]);
		return (NULL);
	}
	else if (ft_strequ(input[0], "env"))
		ft_env(input, envv);
	return (envv);
}

t_envv			*run_builtin(char **input, t_envv *envv, char **arr)
{
	if (!(input[0]))
		return (envv);
	else if (ft_strequ(input[0], "exit"))
	{
		ft_freestrarr(arr);
		ft_freestrarr(input);
		ft_free_tenvv(envv);
		ft_putendl("\033[00;31mminishell get killed\033[00m");
		exit(0);
	}
	else if (ft_strequ(input[0], "pwd"))
		ft_putendl(get_tenvv_val(envv, "PWD"));
	else if (ft_strequ(input[0], "cd"))
		return (ft_cd(input, envv));
	else if (ft_strequ(input[0], "echo"))
		ft_echo(&input[1]);
	else
		return (change_envv(input, envv));
	return (envv);
}
