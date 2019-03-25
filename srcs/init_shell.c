/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:08:41 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void	ft_null(t_shell *sh)
{
	ft_get_set_shell(sh);
	sh->pid = getpid();
	sh->heredoc = 0;
	sh->interactive = FALSE;
	sh->intern = NULL;
	sh->clipboard = NULL;
	sh->alias = NULL;
	sh->txt = NULL;
	sh->hist = NULL;
	sh->process = NULL;
	sh->std[0] = STDIN_FILENO;
	sh->std[1] = STDOUT_FILENO;
	sh->std[2] = STDERR_FILENO;
	sh->env = NULL;
	sh->intern = NULL;
}

int			init_shell(t_shell *sh, char **envv, char **argv)
{
	ft_null(sh);
	if (!(init_env(sh, argv, envv)))
		return (0);
	if (!isatty(0))
	{
		if (exec_fd(sh, 0) == 0)
			error("abort", "no standart input");
		return (0);
	}
	if (argv[1] && !ft_isempty(argv[1]))
	{
		exec_file(argv[1], sh);
		return (0);
	}
	set_signals();
	if (!init_termcaps(sh))
		return (0);
	sh->interactive = TRUE;
	return (1);
}
