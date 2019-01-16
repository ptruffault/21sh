/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/13 13:09:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_delete_line(t_edit *e)
{
	int i;

	i = 0;
	curs_reset(e);
	while (i <= e->t->nb_of_l)
	{
		TERM(DELETE_LINE);
		i++;
	}
}

void		ft_print_line(t_edit *e)
{
	int i;
	int save_x;
	int save_y;

	save_x = e->t->x;
	save_y = e->t->y;
	ft_delete_line(e);
		i = 0;
	while (e->input[i])
	{
		if (e->input[i] == '\t')
			ft_putchar(' ');
		else
			ft_putchar(e->input[i]);
		i++;
	}
	curs_move_to(e, save_x, save_y);
}
