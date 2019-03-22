/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:08:59 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	curs_reset(t_edit *e)
{
	size_t y;

	y = e->pos;
	if (e->width != 0)
	{
		while (y > e->width)
		{
			y = y - e->width;
			term_actions(CURSOR_UP);
		}
	}
	term_goto(CURSOR_MHORIZ, 0, 0);
	e->pos = 0;
}
