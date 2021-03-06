/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void	set_var(char **argv, t_shell *sh)
{
	int i;

	i = 0;
	while (ft_isequal(argv[i]))
		sh->intern = ft_new_envv_equ(sh->intern, argv[i++]);
}

static int	change_envv(char **argv, t_shell *sh)
{
	if (ft_strequ(*argv, "unsetenv") && argv[1])
		sh->env = ft_unsetenv(sh->env, &argv[1]);
	else if (ft_strequ(*argv, "setenv") && argv[1])
		sh->env = ft_setenv(sh->env, &argv[1], 1);
	else if (ft_isequal(*argv))
		set_var(argv, sh);
	else if (ft_strequ(*argv, "unset") && argv[1])
		sh->intern = ft_unsetenv(sh->intern, &argv[1]);
	else if (ft_strequ(*argv, "cd"))
		sh->env = ft_cd(argv, sh->env);
	else if (ft_strequ(*argv, "export"))
		sh->env = ft_export(sh, &argv[1]);
	else if (ft_strequ(*argv, "set"))
		ft_puttenvv(sh->intern);
	else if (ft_strequ(*argv, "alias"))
		ft_alias(sh, argv);
	else if (ft_strequ(*argv, "unalias") && argv[1])
		sh->alias = ft_unsetenv(sh->alias, &argv[1]);
	return (0);
}

int			run_builtin(t_tree *t, char **argv, t_shell *sh)
{
	if (ft_strequ(*argv, "exit"))
		ft_exit(argv[1], sh);
	else if (ft_strequ(*argv, "env"))
		return (ft_env(sh->env, argv));
	else if (ft_strequ(*argv, "echo"))
		return (ft_echo(&argv[1]));
	else if (ft_strequ(*argv, "type"))
		return (ft_type(t->cmd->next, sh));
	return (change_envv(argv, sh));
}
