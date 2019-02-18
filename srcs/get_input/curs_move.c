/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:08:59 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/09 11:20:21 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	curs_reset(t_edit *e)
{
	int y;

	y = e->pos;
	while (y > e->width)
	{
		y = y - e->width;
		term_actions(CURSOR_UP);
	}
	term_goto(CURSOR_MHORIZ, 0, 0);
	e->pos = 0;
}
