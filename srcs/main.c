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

#include <21sh.h>

void		ft_disp(t_shell *sh)
{
	ft_printf("\033[1;32m 21sh\033[00m:[\033[01;34m\033[04m%s\033[00m]\n",
	get_tenvv_val(sh->env, "PWD"));
}

int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;
	char *in;
	
	(void)argc;
	set_signals();
	init_shell(&sh, envv, argv);
	while (42)
	{
		ft_get_set_envv(sh.env);
		ft_disp(&sh);
		ft_setup_edit_term(&sh);
		in = get_input();
		ft_set_old_term(&sh);
		if ((t = get_tree(in)))
			ft_free_tree(exec_tree(ft_get_set_tree(t)));
	}
	return (0);
}