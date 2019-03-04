/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:33:46 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/18 15:36:03 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"

void	ft_disp(t_shell *sh)
{
	ft_printf("\033[1;32m21sh\033[00m:[\033[01;34m\033[04m%s\033[00m]\n",
	get_tenvv_val(sh->env, "PWD"));
}

int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;
	char	*in;

	(void)argc;
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
