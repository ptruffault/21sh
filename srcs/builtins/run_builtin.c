/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:13:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static void	set_var(char **argv, t_shell *sh)
{
	t_envv *head;
	t_envv *end;

	head = ft_setenv(new_tenvv(), argv);
	end = head;
	while (end && end->next)
		end = end->next;
	end->next = sh->intern;
	sh->intern = head;
}

static void	change_envv(char **argv, t_shell *sh)
{
	if (ft_strequ(*argv, "unsetenv") && argv[1])
		sh->env = ft_unsetenv(sh->env, &argv[1]);
	else if (ft_strequ(*argv, "setenv") && argv[1])
		sh->env = ft_setenv(sh->env, &argv[1]);
	else if (ft_strequ(*argv, "jobs"))
		ft_jobs(sh);
	else if (ft_isequal(*argv))
		set_var(argv, sh);
	else if (ft_strequ(*argv, "unset") && argv[1])
		sh->intern = ft_unsetenv(sh->intern, &argv[1]);
	else if (ft_strequ(*argv, "cd"))
		sh->env = ft_get_set_envv(ft_cd(argv, sh->env));
	else if (ft_strequ(*argv, "export"))
		sh->env = ft_get_set_envv(ft_export(sh, &argv[1]));
	else if (ft_strequ(*argv, "set"))
		ft_puttenvv(sh->intern);
	else if (ft_strequ(*argv, "alias"))
		ft_alias(sh, argv);
	else if (ft_strequ(*argv, "unalias") && argv[1])
		sh->alias = ft_unsetenv(sh->alias, &argv[1]);
}

static void	ft_redir(t_tree *t, int fd[3])
{
	fd[0] = 0;
	fd[1] = 1;
	fd[2] = 2;
	if (t->r && ft_redirect_builtin(t, fd) == -1)
		warning("redirection fucked up", NULL);
}

int			run_builtin(t_tree *t, char **argv)
{
	t_shell *sh;
	int		fd[3];

	sh = ft_get_set_shell(NULL);
	ft_redir(t, fd);
	if (ft_strequ(*argv, "exit"))
		ft_exit();
	else if (ft_strequ(*argv, "env"))
		ft_env(sh->env, argv);
	else if (ft_strequ(*argv, "echo"))
		ft_echo(&argv[1]);
	else if (ft_strequ(*argv, "type"))
		ft_type(t->cmd->next);
	else if (ft_strequ(*argv, "42"))
		exec_file(argv[1]);
	else
		change_envv(argv, sh);
	if (t->r)
		ft_reset_fd(fd);
	return (0);
}
