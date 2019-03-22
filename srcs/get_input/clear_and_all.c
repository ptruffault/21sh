/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:57:43 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/21 16:26:21 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	setup_key(char *error[7])
{
	error[0] = "cmdand";
	error[1] = "cmdor";
	error[2] = "pipe";
	error[3] = "quote";
	error[4] = "dquote";
	error[5] = "backslash";
	error[6] = "parenth";
}

void	entry_key(t_edit *e)
{
	t_eval	eval;
	char	*error[7];

	setup_key(error);
	lexer(&eval, e->hist->s);
	ft_strdel(&eval.eval);
	ft_strdel(&eval.s);
	if (eval.err > 1)
	{
		if (eval.err == 6 || eval.err == 5)
		{
			ft_add_char('\\', e);
			ft_add_char('n', e);
		}
		else
		{
			ft_printf("\n\033[00;31m%s\033[00m >\n", error[eval.err - 2]);
			ft_putstr(e->hist->s);
		}
	}
	else
		e->edited = TRUE;
}

void	clear_term(t_edit *e)
{
	term_actions(HOME_POS);
	term_actions(CLEAR);
	e->pos = 0;
}

void	reset_get_input(t_edit *e)
{
	while (e->hist->prev)
		e->hist = e->hist->prev;
	ft_strdel(&e->hist->s);
	if (e->hist->next)
		e->hist->next->prev = NULL;
	free(e->hist);
}

void	just_exit(t_edit *e)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	if (sh->heredoc == 1)
	{
		sh->heredoc = 0;
		sh->e.edited = TRUE;
	}
	if (!e->hist || !e->hist->s || !*e->hist->s)
	{
		ft_strdel(&e->hist->s);
		free(e->hist);
		e->hist = NULL;
	}
}
