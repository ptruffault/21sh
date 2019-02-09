/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:10:54 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

void		ft_echo(char **input)
{
	int i;
	int opts_n;

	i = 0;
	opts_n = 0;
	while (input[i])
	{
		if (i > 0)
			ft_putchar('\t');
		if (ft_strequ(input[i], "-n") && input[++i])
			opts_n = 1;
		ft_putstr(input[i++]);
	}
	if (opts_n)
		ft_putchar(0);
	else
		ft_putchar('\n');
}
