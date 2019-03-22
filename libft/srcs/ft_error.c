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

#include <libft.h>

int	error(char *descript, char *opts)
{
	ft_putstr_fd("\a\033[04m\033[00;31mError: \033[00m", STDERR_FILENO);
	ft_putstr_fd(descript, STDERR_FILENO);
	if (opts && *opts)
	{
		ft_putstr_fd(" \033[1;32m(\033[00m", STDERR_FILENO);
		ft_putstr_fd(opts, STDERR_FILENO);
		ft_putstr_fd("\033[1;32m)\033[00m", STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (0);
}

int	error_c(char *descript, char opts)
{
	ft_putstr_fd("\a\033[04m\033[00;31mError: \033[00m", STDERR_FILENO);
	ft_putstr_fd(descript, STDERR_FILENO);
	ft_putstr_fd(" \033[1;32m(\033[00m", STDERR_FILENO);
	ft_putchar_fd(opts, STDERR_FILENO);
	ft_putstr_fd("\033[1;32m)\033[00m\n", STDERR_FILENO);
	return (0);
}

int	error_i(char *descript, int i)
{
	ft_putstr_fd("\a\033[04m\033[00;31mError: \033[00m", STDERR_FILENO);
	ft_putstr_fd(descript, STDERR_FILENO);
	ft_putstr_fd("  --> \033[1;32m", STDERR_FILENO);
	ft_putnbr_fd(i, STDERR_FILENO);
	ft_putstr_fd("\033[00m\n", STDERR_FILENO);
	return (0);
}

int	warning(char *descript, char *opts)
{
	ft_putstr_fd("\a\033[04m\033[1;35mWarning: \033[00m", STDERR_FILENO);
	ft_putstr_fd(descript, STDERR_FILENO);
	if (opts && *opts)
	{
		ft_putstr_fd(" \033[1;32m(\033[00m", STDERR_FILENO);
		ft_putstr_fd(opts, STDERR_FILENO);
		ft_putstr_fd("\033[1;32m)\033[00m", STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (0);
}

int	warning_c(char *descript, char opts)
{
	ft_putstr_fd("\a\033[04m\033[1;35mWarning: \033[00m", STDERR_FILENO);
	ft_putstr_fd(descript, STDERR_FILENO);
	ft_putstr_fd(" \033[1;32m(\033[00m", STDERR_FILENO);
	ft_putchar_fd(opts, STDERR_FILENO);
	ft_putstr_fd("\033[1;32m)\033[00m\n", STDERR_FILENO);
	return (0);
}
