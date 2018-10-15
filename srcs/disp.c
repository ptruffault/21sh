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

#include "../includes/21sh.h"

static void	ft_p1(t_envv *e)
{
	ft_putstr("\033[00m\n");
	ft_putstr(get_tenvv_val(e, "PWD"));
	ft_putchar('>');
}

static void	ft_p2(t_envv *e)
{
	ft_putstr("\033[1;32m");
	ft_putstr(get_tenvv_val(e, "PWD"));
	ft_putstr("\033[00m");
	ft_putchar('>');
}

static void	ft_p3(t_envv *e)
{
	ft_putstr("\033[1;32m");
	ft_putstr(get_tenvv_val(e, "USER"));
	ft_putstr("\033[00m:\033[04m\033[01;34m");
	ft_putstr(get_tenvv_val(e, "PWD"));
	ft_putstr("\033[00m >");
}

static void	ft_p4(t_envv *e)
{
	ft_putstr(VERT);
	ft_putstr("\033[04m va bien te faire enculé\033[00m:\033[04m\033[01;34m");
	ft_putstr(ROUGE);
	ft_putstr(get_tenvv_val(e, "USER"));
	ft_putstr(NORMAL);
}

void		ft_disp(t_envv *envv, int argc, char **argv)
{
	if (argc != 1)
	{
		if (argv[1][0] == '0')
			ft_p1(envv);
		else if (argv[1][0] == '1')
			ft_p2(envv);
		else if (argv[1][0] == '2')
			ft_p3(envv);
		else if (argv[1][0] == '3')
			ft_putstr("\033[1;32m->\033[00m");
		else if (argv[1][0] == '4')
			ft_p4(envv);
	}
	else
	{
		ft_putstr("\033[1;32m21sh\033[00m:[\033[01;34m\033[04m");
		ft_putstr(get_tenvv_val(envv, "PWD"));
		ft_putendl("\033[00m]");
	}
}
