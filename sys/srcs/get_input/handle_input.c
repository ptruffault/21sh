/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:14:33 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/05 12:34:30 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_home_key(t_edit *e)
{
	e->curr = 0;
}

void	ft_init_inputs_kval(unsigned long kval[])
{
	kval[0] = KEY_ENTER;
	kval[1] = ARROW_LEFT;
	kval[2] = ARROW_RIGHT;
	kval[3] = TOUCHE_HOME;
	kval[4] = TOUCHE_END;
	kval[5] = TOUCHE_JP_MOT_RIGHT;
	kval[6] = TOUCHE_JP_MOT_LEFT;
	kval[7] = TOUCHE_CMD_C;
	kval[8] = TOUCHE_CMD_V;
	kval[9] = TOUCHE_CTRL_D;
	kval[10] = ARROW_UP;
	kval[11] = ARROW_DOWN;
	kval[12] = TOUCHE_SUPPR;
	kval[13] = TOUCHE_DEL;
	kval[14] = TOUCHE_CTRL_L;
	kval[15] = TOUCHE_SELECT_LEFT;
	kval[16] = TOUCHE_SELECT_RIGHT;
}

void	ft_init_inputs_tab(unsigned long kval[], void (*ft_tab[])(t_edit *e))
{
	ft_init_inputs_kval(kval);
	ft_tab[0] = entry_key;
	ft_tab[1] = curr_move_left;
	ft_tab[2] = curr_move_right;
	ft_tab[3] = ft_home_key;
	ft_tab[4] = curr_go_last;
	ft_tab[5] = ft_jp_word_right;
	ft_tab[6] = ft_jp_word_left;
	ft_tab[7] = ft_copy;
	ft_tab[8] = ft_paste;
	ft_tab[9] = just_exit;
	ft_tab[10] = hist_move_up;
	ft_tab[11] = hist_move_do;
	ft_tab[12] = delete_left;
	ft_tab[13] = delete_on;
	ft_tab[14] = clear_term;
	ft_tab[15] = ft_select_left;
	ft_tab[16] = ft_select_right;
}

int		handle_input(unsigned long buf, t_edit *e)
{
	int				x;
	unsigned long	kval[17];
	void			(*ft_tab[17])(t_edit *e);

	ft_init_inputs_tab(kval, ft_tab);
	x = -1;
	while (++x < 17)
	{
		if (kval[x] == buf)
		{
			if (x != 15 && x != 16 && x != 7)
				e->select = -1;
			ft_tab[x](e);
			break ;
		}
	}
	if (x == 17 && ft_isascii(buf))
		ft_add_char((char)buf, e);
	return (x);
}
