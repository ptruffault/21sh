 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"

void	ft_disp(t_shell *sh)
{
	ft_printf("\033[1;32m 21sh\033[00m:[\033[01;34m\033[04m%s\033[00m]\n",
	get_tenvv_val(sh->env, "PWD"));
}

int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;
	char	*in;

	(void)argc;
	set_signals();
	ft_get_set_shell(&sh);
	init_shell(&sh, envv, argv);
	while (42)
	{
		ft_disp(&sh);
		in = get_input();
		if ((t = get_tree(in)))
			ft_free_tree(exec_tree(ft_get_set_tree(t)));
		ft_strdel(&in);
	}
	return (0);
}
