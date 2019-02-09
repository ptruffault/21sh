/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:34:45 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 16:34:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstrarr_fd(char **t, int fd)
{
	int i;

	i = 0;
	while ((t[i]))
	{
		ft_putstr_fd(t[i++], fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_putstrarr(char **t)
{
	ft_putstrarr_fd(t, 1);
}
