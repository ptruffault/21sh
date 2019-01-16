/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:14:33 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/13 13:14:34 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_input.h"

static void	curr_move_right(t_edit *e)
{
	if (e->curr + 1 < e->size)
	{
		e->curr++;
		curs_move_right(e);
	}
}

static void	curr_move_left(t_edit *e)
{
	if (e->curr > 0)
	{
		e->curr--;
		curs_move_left(e);
	}
}

void curs_go_last(t_edit *e)
{
	curs_move_to(e, -1, -1);
}

void input_end(t_edit *e)
{
	e->edited = TRUE;
}

void clear_term(t_edit *e)
{
	TERM(CLEAR);
	(void)e;
}

void reset_input(t_edit *e)
{
	update_input(e, NULL);
	e->edited = TRUE;
}

void ft_init_inputs_tab(unsigned long kval[], void (*ft_tab[])(t_edit *e))
{
	kval[0] = KEY_ENTER;
	kval[1] = ARROW_LEFT;
	kval[2] = ARROW_RIGHT;
	kval[3] = ARROW_UP;
	kval[4] = ARROW_DOWN;
	kval[5] = TOUCHE_SUPPR;
	kval[6] = TOUCHE_DEL;
	kval[7] = TOUCHE_HOME;
	kval[8] = TOUCHE_END;
	kval[9] = TOUCHE_CTRL_L;
	kval[10] = TOUCHE_CTRL_C;
	ft_tab[0] = input_end;
	ft_tab[1] = curr_move_left;
	ft_tab[2] = curr_move_right;
	ft_tab[3] = hist_move_up;
	ft_tab[4] = hist_move_do;
	ft_tab[5] = delete_left;
	ft_tab[6] = delete_on;
	ft_tab[7] = curs_reset;
	ft_tab[8] = curs_go_last;
	ft_tab[9] = clear_term;
	ft_tab[10] = reset_input;
}

void		handle_input(unsigned long buf, t_edit *e)
{
	int x;
	unsigned long kval[11];
	void (*ft_tab[11])(t_edit *e);

	ft_init_inputs_tab(kval, ft_tab);
	x = -1;
	while (++x < 11)
	{
		if (kval[x] == buf)
		{
			//printf("[%d]\n", x);
			ft_tab[x](e);
			break;
		}
	}
	//printf("[%d]\n", x);
	if (x == 11 && ft_isascii(buf))
		ft_add_char((char)buf,e);
}
