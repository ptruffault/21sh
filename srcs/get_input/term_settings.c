/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:32:55 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/22 16:27:20 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	ft_update_windows(t_edit *e)
{
	struct winsize	window;

	if ((ioctl(0, TIOCGWINSZ, &window)) == 0)
		e->width = window.ws_col;
	else
		e->width = 0;
}

int		init_termcaps(t_shell *sh)
{
	char *term;

	term = NULL;
	if (((term = get_tenvv_val(sh->env, "TERM")) && !tgetent(NULL, term)))
		return (error("can't retrieve terminal informations", term));
	if (!(tgetstr("ch", NULL))
		|| !(tgetstr("cd", NULL)) || !(tgetstr("up", NULL)))
		return (error("term doesn't support necassary termcaps", term));
	if (tcgetattr(0, &sh->saved_term) == -1)
		return (error("can't save termios", term));
	ft_update_windows(&sh->e);
	return (1);
}

int		ft_setup_edit_term(t_shell *sh)
{
	char *term;

	term = NULL;
	if (((term = get_tenvv_val(sh->env, "TERM")) && !tgetent(NULL, term)))
		return (error("can't retrieve terminal informations", term));
	if (!(tgetstr("ch", NULL))
		|| !(tgetstr("cd", NULL)) || !(tgetstr("up", NULL)))
		return (error("term doesn't support necassary termcaps", term));
	ft_memcpy(&sh->term, &sh->saved_term, sizeof(struct termios));
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

int		ft_set_old_term(t_shell *sh, int error)
{
	if ((tcsetattr(0, TCSADRAIN, &sh->saved_term)) == -1)
		warning("can't load old term setting", NULL);
	return (error);
}
