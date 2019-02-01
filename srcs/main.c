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

void		ft_disp(int argc, char **argv)
{
	char *pwd;

	(void)argv;
	(void)argc;
	pwd = get_tenvv_val(ft_get_set_envv(NULL), "PWD");
	ft_printf("\033[1;32m 21sh\033[00m:[\033[01;34m\033[04m%s\033[00m]\n", pwd);
}

void close_term(t_shell *sh)
{
	sh->term.c_lflag &= ~(ICANON | ECHO);
	if ((tcsetattr(0, TCSADRAIN, &sh->term)) == -1)
		warning("Error while set attr of term, not termcaps", NULL);
}


int		main(int argc, char **argv, char **envv)
{
	t_shell	sh;
	t_tree	*t;
	char *in;
	
	set_signals();
	init_shell(&sh, envv, argv);
	while (42)
	{
		ft_get_set_envv(sh.env);
		ft_disp(argc, argv);
		in = get_input();
		if ((t = get_tree(in)))
			ft_free_tree(exec_tree(ft_get_set_tree(t)));
	}
	return (0);
}