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

#include <21sh.h>

int				check_builtin(char **input)
{
	if (input && input[0] && (ft_strequ(input[0], "env") || ft_strequ(input[0], "exit")
	|| ft_strequ(input[0], "unsetenv") || ft_strequ(input[0], "unset") 
	|| ft_strequ(input[0], "setenv") || ft_strequ(input[0], "cd") 
	|| ft_strequ(input[0], "echo") || ft_isequal(input[0])))
		return (1);
	return (0);
}

static t_envv	*change_envv(t_tree *t, t_envv *envv)
{
	if (ft_strequ(t->arr[0], "unsetenv") || ft_strequ(t->arr[0], "unset"))
		return (ft_unsetenv(envv, &t->arr[1]));
	else if (ft_strequ(t->arr[0], "setenv") || ft_isequal(t->arr[0]))
		return (ft_setenv(envv, t->arr));
	else if (ft_strequ(t->arr[0], "cd"))
		return (ft_cd(t->arr, envv));
	return (envv);
}

void ft_exit(t_tree *t, t_envv *e)
{
	ft_free_tree(t);
	ft_free_tenvv(e);
	ft_putendl("\033[00;31m21sh get killed\033[00m");
	exit(0);
}

int run_builtin(t_tree *t)
{
	t_envv *envv;
	int fd[3];

	fd[0] = 0;
	fd[1] =  1;
	fd[2] = 2;
	if(t->r && ft_redirect_builtin(t, fd) == -1)
		warning("redirection fucked up", NULL);
	envv = ft_get_set_envv(NULL);
	if (ft_strequ(t->arr[0], "exit"))
		ft_exit(t, envv);
	else if (ft_strequ(t->arr[0], "env"))
		ft_env(t, envv);
	else if (ft_strequ(t->arr[0], "echo"))
		ft_echo(&t->arr[1]);
	else
		ft_get_set_envv(change_envv(t, envv));
	if (t->r)
		ft_reset_fd(fd);
	return (0);
}

