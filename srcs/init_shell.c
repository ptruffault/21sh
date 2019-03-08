/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:08:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/19 14:00:37 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"

static void	ft_null(t_shell *sh, char **envv)
{
	ft_get_set_shell(sh);
	sh->pid = getpid();
	sh->heredoc = 0;
	sh->intern = NULL;
	sh->saved_term = NULL;
	sh->clipboard = NULL;
	sh->alias = NULL;
	sh->txt = NULL;
	sh->saved_term = NULL;
	sh->process = NULL;
	sh->env = init_tenvv(envv);
}

void		init_shell(t_shell *sh, char **envv, char **argv)
{
	ft_null(sh, envv);
	init_env(sh, argv);
	set_signals();
	if (!isatty(0))
	{
		if (exec_fd(sh, 0) == 0)
			error("abort", "no standart input");
		ft_free_tshell(sh);
		exit(0);
	}
	if (argv[1] && !ft_isempty(argv[1]))
	{
		exec_file(argv[1], sh);
		ft_free_tshell(sh);
		exit(0);
	}
	init_termcaps(sh);
}
