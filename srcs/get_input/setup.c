/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:23:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/22 16:26:58 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

static	void	ft_init_print_modes(t_edit *e, int x)
{
	e->print_modes[x++] = ft_print_fast;
	e->print_modes[x++] = ft_print_edited;
}

static	void	ft_init_inputs_kval(t_edit *e, int x)
{
	e->kval[x++] = KEY_ENTER;
	e->kval[x++] = KEY_ARROW_UP;
	e->kval[x++] = KEY_ARROW_DOWN;
	e->kval[x++] = KEY_ARROW_LEFT;
	e->kval[x++] = KEY_ARROW_RIGHT;
	e->kval[x++] = KEY_OPTION_ARROW_UP;
	e->kval[x++] = KEY_OPTION_ARROW_DOWN;
	e->kval[x++] = KEY_OPTION_ARROW_LEFT;
	e->kval[x++] = KEY_OPTION_ARROW_RIGHT;
	e->kval[x++] = KEY_CTRL_C;
	e->kval[x++] = KEY_CTRL_D;
	e->kval[x++] = KEY_HOME;
	e->kval[x++] = KEY_END;
	e->kval[x++] = KEY_OPTION_C;
	e->kval[x++] = KEY_BACKSPACE;
	e->kval[x++] = KEY_DELETE;
	e->kval[x++] = KEY_OPTION_V;
	e->kval[x++] = KEY_SHIFT_ARROW_UP;
	e->kval[x++] = KEY_SHIFT_ARROW_DOWN;
	e->kval[x++] = KEY_SHIFT_ARROW_LEFT;
	e->kval[x++] = KEY_SHIFT_ARROW_RIGHT;
	e->kval[x++] = KEY_SHIFT_HOME;
	e->kval[x++] = KEY_SHIFT_END;
}

static	void	ft_init_inputs_tab(t_edit *e, int x)
{
	ft_init_inputs_kval(e, 0);
	ft_init_print_modes(e, 0);
	e->ft_tab[x++] = entry_key;
	e->ft_tab[x++] = hist_move_up;
	e->ft_tab[x++] = hist_move_do;
	e->ft_tab[x++] = curr_move_left;
	e->ft_tab[x++] = curr_move_right;
	e->ft_tab[x++] = ft_jump_line_up;
	e->ft_tab[x++] = ft_jump_line_down;
	e->ft_tab[x++] = ft_jp_word_left;
	e->ft_tab[x++] = ft_jp_word_right;
	e->ft_tab[x++] = reset_get_input;
	e->ft_tab[x++] = just_exit;
	e->ft_tab[x++] = ft_home_key;
	e->ft_tab[x++] = curr_go_last;
	e->ft_tab[x++] = ft_copy;
	e->ft_tab[x++] = delete_left;
	e->ft_tab[x++] = delete_on;
	e->ft_tab[x++] = ft_paste;
	e->ft_tab[x++] = ft_select_line_up;
	e->ft_tab[x++] = ft_select_line_down;
	e->ft_tab[x++] = ft_select_left;
	e->ft_tab[x++] = ft_select_right;
	e->ft_tab[x++] = ft_select_home;
	e->ft_tab[x++] = ft_select_end;
}

static int		ft_init_input_link(t_shell *sh)
{
	t_hist	*tmp;

	sh->e.hist = tmp;
	if (sh->hist)
	{
		tmp->next = sh->hist;
		tmp->next->prev = tmp;
	}
	if (!(tmp->s = ft_strnew(2)))
	{
		free(tmp);
		return (FAILURE);
	}
	return (SUCCESS);
}

int				init_tedit(t_shell *sh)
{
	ft_update_windows(&sh->e);
	ft_init_inputs_tab(&sh->e, 0);
	sh->e.edited = FALSE;
	sh->e.curr = 0;
	sh->e.pos = 0;
	sh->e.select = -1;
	sh->e.select_pos = 0;
	sh->e.mode = 0;
	sh->e.hist = NULL;
	if ((tmp = new_hist()) || ft_init_input_link(sh) == FAILURE)
		return (FAILURE);
	else
		return (FAILURE);
	return (SUCCESS);
}
