/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:48:14 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/11 12:48:16 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	error(char *descript, char *opts)
{
	ft_putstr_fd("\a\033[04m\033[00;31mError: \033[00m", 2);
	ft_putstr_fd(descript, 2);
	if (opts)
	{
		ft_putstr_fd(" \033[1;32m(\033[00m", 2);
		ft_putstr_fd(opts, 2);
		ft_putstr_fd("\033[1;32m)\033[00m", 2);
	}
	ft_putchar_fd('\n', 2);
}

void	error_c(char *descript, char opts)
{
	ft_putstr_fd("\a\033[04m\033[00;31mError: \033[00m", 2);
	ft_putstr_fd(descript, 2);
	ft_putstr_fd(" \033[1;32m(\033[00m", 2);
	ft_putchar_fd(opts, 2);
	ft_putstr_fd("\033[1;32m)\033[00m\n", 2);
}

void	warning(char *descript, char *opts)
{
	ft_putstr_fd("\a\033[04m\033[1;35mWarning: \033[00m", 2);
	ft_putstr_fd(descript, 2);
	if (opts)
	{
		ft_putstr_fd(" \033[1;32m(\033[00m", 2);
		ft_putstr_fd(opts, 2);
		ft_putstr_fd("\033[1;32m)\033[00m", 2);
	}
	ft_putchar_fd('\n', 2);
}

void	warning_c(char *descript, char opts)
{
	ft_putstr_fd("\a\033[04m\033[1;35mWarning: \033[00m", 2);
	ft_putstr_fd(descript, 2);
	ft_putstr_fd(" \033[1;32m(\033[00m", 2);
	ft_putchar_fd(opts, 2);
	ft_putstr_fd("\033[1;32m)\033[00m\n", 2);
}
