/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:23:52 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/13 13:23:53 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_input.h"

static void	setup_term(t_edit *e)
{
	struct winsize	window;

	if (tgetent(NULL, get_tenvv_val(ft_get_set_envv(NULL), "TERM")) != 1)
		warning("$TERM not valid, no termcaps", NULL);
	if (!(e->t = (t_termi *)malloc(sizeof(t_termi))))
		warning("malloc error", "t_termi");
	if (tcgetattr(0, &e->t->term) == -1)
		warning("Error while get attr of term, no termcaps", NULL);
	e->t->term.c_lflag &= ~(ICANON);
	e->t->term.c_lflag &= ~(ECHO);
	e->t->term.c_cc[VMIN] = 1;
	e->t->term.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSADRAIN, &e->t->term)) == -1)
		warning("Error while set attr of term, not termcaps", NULL);
	ioctl(0, TIOCGWINSZ, &window);
	TERM(UNDERLINE_CURS);
	TERM(SAVE_CURS);
	e->t->width = window.ws_col;
	e->t->nb_of_l = 0;
	e->t->x = 0;
	e->t->y = 0;
}

t_edit		init_tedit(void)
{
	t_edit e;

	e.edited = FALSE;
	e.curr = 0;
	e.size = 1;
	e.input = ft_strnew(2);
	setup_term(&e);
	e.curr_history = 0;
	get_hist_path(&e);
	return (e);
}

void		free_tedit(t_edit *e)
{
	if (e->t != NULL)
	{
		if (tcgetattr(0, &e->t->term) == -1)
			warning("can't reset term", NULL);
		e->t->term.c_lflag = (ICANON | ECHO);
		if (tcsetattr(0, 0, &e->t->term) == -1)
			warning("can't reset term", NULL);
		free(e->t);
	}
	ft_strdel(&e->input);
	e = NULL;
}
