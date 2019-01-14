/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:08:59 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/13 13:09:00 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	curs_reset(t_edit *e)
{
	TERM(RESET_CURS);
	e->t->x = 0;
	e->t->y = 0;
}

void	curs_move_to(t_edit *e, int x, int y)
{
	curs_reset(e);
	if (y * e->t->width + x > e->size || (x == -1 && y == -1))
	{
		x = e->size - e->t->nb_of_l * e->t->width - 1;
		y = (e->size - x) / e->t->width;
	}
	while (e->t->y != y)
	{
		TERM(CURSEUR_DO);
		e->t->y++;
	}
	while (e->t->x != x)
		curs_move_right(e);
}

void	curs_move_left(t_edit *e)
{
	if (e->t->x > 0)
	{
		TERM(CURSEUR_LE);
		e->t->x--;
	}
	else if (e->t->y > 0)
	{
		TERM(CURSEUR_UP);
		e->t->y--;
		while (e->t->x < (e->t->y + 1) * e->t->width)
		{
			TERM(CURSEUR_RI);
			e->t->x++;
		}
	}
}

void	curs_move_right(t_edit *e)
{
	if (e->t->x < e->t->width)
	{
		TERM(CURSEUR_RI);
		e->t->x++;
	}
	else
	{
		TERM(CURSEUR_DO);
		e->t->y++;
		if (e->t->y > e->t->nb_of_l)
			e->t->nb_of_l = e->t->y;
		while (e->t->x > 1)
		{
			TERM(CURSEUR_LE);
			e->t->x--;
		}
	}
}
