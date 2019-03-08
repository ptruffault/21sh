/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:32:55 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/08 13:31:10 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_update_windows(t_edit *e)
{
	struct winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	e->width = window.ws_col;
}

void	init_termcaps(t_shell *sh)
{
	char *term;

	term = NULL;
	if (((term = get_tenvv_val(sh->env, "TERM")) && !tgetent(NULL, term)))
		tgetent(NULL, "xterm-256color");
	if ((sh->saved_term = (struct termios *)malloc(sizeof(struct termios)))
	&& (tcgetattr(0, sh->saved_term) == -1))
	{
		error("can't save termios", NULL);
		ft_free_tshell(sh);
		ft_free_tree(ft_get_set_tree(NULL));
		exit(0);
	}
	ft_update_windows(&sh->e);
}

int		ft_setup_edit_term(t_shell *sh)
{
	char *term;

	term = NULL;
	if (!sh->saved_term)
		return (0);
	if (((term = get_tenvv_val(sh->env, "TERM")) && !tgetent(NULL, term)))
		tgetent(NULL, "xterm-256color");
	ft_memcpy(&sh->term, sh->saved_term, sizeof(struct termios));
	sh->term.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOKE
			| ECHONL | ECHOCTL | ISIG);
	sh->term.c_cc[VMIN] = 1;
	sh->term.c_cc[VTIME] = 0;
	sh->term.c_cc[VINTR] = 3;
	sh->term.c_cc[VEOF] = 4;
	if ((tcsetattr(0, TCSADRAIN, &sh->term)) == -1)
		return (0);
	return (1);
}

void	ft_set_old_term(t_shell *sh)
{
	if (sh->saved_term && (tcsetattr(0, TCSADRAIN, sh->saved_term)) == -1)
		warning("can't load old term setting", NULL);
}
