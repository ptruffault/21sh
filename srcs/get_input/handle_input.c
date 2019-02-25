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

void	ft_init_inputs_kval(unsigned long kval[])
{
	kval[0] = KEY_ENTER;
	kval[1] = ARROW_LEFT;
	kval[2] = ARROW_RIGHT;
	kval[3] = TOUCHE_HOME;
	kval[4] = TOUCHE_END;
	kval[5] = TOUCHE_OPT_RIGHT;
	kval[6] = TOUCHE_OPT_LEFT;
	kval[7] = TOUCHE_OPT_C;
	kval[8] = TOUCHE_OPT_V;
	kval[9] = TOUCHE_CTRL_D;
	kval[10] = ARROW_UP;
	kval[11] = ARROW_DOWN;
	kval[12] = TOUCHE_SUPPR;
	kval[13] = TOUCHE_DEL;
	kval[14] = TOUCHE_CTRL_L;
	kval[15] = TOUCHE_SELECT_LEFT;
	kval[16] = TOUCHE_SELECT_RIGHT;
	kval[17] = TOUCHE_MAJ_END;
	kval[18] = TOUCHE_MAJ_HOME;
	kval[19] = TOUCHE_MAJ_ARROW_UP;
	kval[20] = TOUCHE_MAJ_ARROW_DOWN;
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
	ft_tab[17] = ft_select_end;
	ft_tab[18] = ft_select_home;
	ft_tab[19] = ft_jump_line_up;
	ft_tab[20] = ft_jump_line_down;
}

int		handle_input(unsigned long buf, t_edit *e)
{
	int				x;
	unsigned long	kval[21];
	void			(*ft_tab[21])(t_edit *e);

	ft_init_inputs_tab(kval, ft_tab);
	x = -1;
	while (++x < 21)
	{
		if (kval[x] == buf)
		{
			if (x != 7 && x < 12)
				e->select = -1;
			ft_tab[x](e);
			break ;
		}
	}
	if (x == 21 && ft_isascii(buf))
		ft_add_char((char)buf, e);
	return (x);
}
