/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:14:33 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

int		handle_input(unsigned long buf, t_edit *e)
{
	int				x;

	x = -1;
	while (++x < NUMBER_OF_KEYS)
	{
		if (e->kval[x] == buf)
		{
			if (x < 13)
			{
				e->select = -1;
				e->select_pos = 0;
			}
			e->ft_tab[x](e);
			if (x == 9 || x == 10)
				return (x);
			break ;
		}
	}
	if (x == NUMBER_OF_KEYS && ft_isascii(buf) && e->hist)
		if (!(ft_add_char((char)buf, e)))
			return (9);
	return (x);
}
