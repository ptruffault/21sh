/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/22 16:07:10 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void		ft_delete_line(t_edit *e)
{
	curs_reset(e);
	term_actions("cd");
}

static void	print_background(t_edit *e, int pos, int size)
{
	ft_putstr(JAUNE);
	term_actions("mr");
	write(1, e->hist->s + pos, size);
	ft_putstr(NORMAL);
	term_actions("me");
}

void		ft_print_edited(t_edit *e)
{
	ft_delete_line(e);
	e->curr = ft_strlen(e->hist->s);
	ft_putstr("\x1B[33m");
	write(1, e->hist->s, e->curr);
	ft_putstr(NORMAL);
	term_actions("ve");
	ft_putchar('\n');
}

void		ft_print_fast(t_edit *e)
{
	size_t pos;
	size_t size;
	size_t i;

	ft_delete_line(e);
	pos = 0;
	size = 1;
	term_actions((e->curr == ft_strlen(e->hist->s)) ? "ve" : "vi");
	i = ft_strlen(e->hist->s);
	if (e->select == -1 || e->select_pos == e->curr)
		pos = e->curr;
	else
	{
		pos = (e->select_pos > e->curr) ? e->curr : e->select_pos;
		if (e->select_pos > e->curr)
			size += e->select_pos - e->curr;
		else
			size += e->curr - e->select_pos;
	}
	write(1, e->hist->s, pos);
	print_background(e, pos, size);
	if (e->curr != i && e->select_pos != i)
		write(1, e->hist->s + pos + size, i - pos - size);
	e->pos = i;
}

void		ft_print_line(t_edit *e)
{
	if (e && e->hist && e->hist->s)
		e->print_modes[e->mode](e);
}
