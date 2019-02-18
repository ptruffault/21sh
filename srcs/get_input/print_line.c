/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/09 11:21:49 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"
#include <curses.h>

void		ft_delete_line(t_edit *e)
{
	curs_reset(e);
	term_actions("cd");
}

static void	print_background(t_edit *e, int i)
{
	ft_putstr(JAUNE);
	ft_putstr(tparm(tgetstr("AB", NULL), COLOR_WHITE));
	ft_putchar(e->input[i]);
	ft_putstr(NORMAL);
	term_actions("me");
}

void		ft_print_line(t_edit *e)
{
	int	i;

	ft_delete_line(e);
	i = 0;
	term_actions((size_t)e->curr == ft_strlen(e->input) ? "ve" : "vi");
	while (e->input[i])
	{
		if (e->input[i] == '\t')
			ft_putchar(' ');
		else if (i == e->curr)
			print_background(e, i);
		else if (e->select != -1
				&& ((i >= e->select && i <= e->curr)
					|| (i >= e->curr && i <= e->select)))
			print_background(e, i);
		else
			ft_putchar(e->input[i]);
		i++;
	}
	e->pos = i;
}
