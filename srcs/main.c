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
	(void)argv;
	(void)argc;
	ft_putstr("\033[1;32m21sh\033[00m:[\033[01;34m\033[04m");
	ft_putstr(get_tenvv_val(ft_get_set_envv(NULL), "PWD"));
	ft_putendl("\033[00m]");
}


int		main(int argc, char **argv, char **envv)
{
	t_envv	*my_envv;
	t_tree	*t;
	char *input;

	set_signals();
	if (!(my_envv = new_tenvv()))
		return (-1);
	my_envv = ft_get_set_envv(init_tenvv(my_envv, envv));
	while (42)
	{
		ft_disp(argc, argv);
		if ((input = get_input(envv))
		{
			if ((t = get_tree(input)))
			{
				exec_tree(t);
				ft_free_tree(t);
			}
		}
	}
	return (0);
}