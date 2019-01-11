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

void ft_put_tword(t_word *w)
{
	while(w)
	{
		printf("\'%s\'  type = %i\n",w->word , w->type);
		w = w->next;
	}
}




int		main(int argc, char **argv, char **envv)
{
	t_shell	e_shell;
	t_tree	*t;

	set_signals();
	init_shell(&e_shell, argv, envv);
	while (42)
	{
		ft_disp(argc, argv);
		ft_get_set_envv(e_shell.env);
		if ((t = ft_get_set_tree(get_tree(get_input()))))
		{
			exec_tree(t);
			ft_free_tree(t);
		}
	}
	return (0);
}