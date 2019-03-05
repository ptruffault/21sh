/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:57:43 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/08 13:37:26 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	entry_key(t_edit *e)
{
	t_eval	eval;
	char	*error[7];

	error[0] = "cmdand";
	error[1] = "cmdor";
	error[2] = "pipe";
	error[3] = "quote";
	error[4] = "dquote";
	error[5] = "backslash";
	error[6] = "parenth";
	eval = lexer(e->input);
	ft_strdel(&eval.eval);
	if (eval.err > 1)
	{
		ft_printf("\n\033[00;31m%s\033[00m >\n", error[eval.err - 2]);
		ft_putstr(e->input);
		e->pos = ft_strlen(e->input);
		e->curr = e->pos;
	}
	else
		e->edited = TRUE;
}

void	clear_term(t_edit *e)
{
	term_actions(CLEAR);
	term_actions(HOME_POS);
	ft_putstr(e->input);
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
	else if (!e->input[0])
	{
		ft_set_old_term(sh);
		ft_free_tshell(sh);
		exit(4);
	}
}
