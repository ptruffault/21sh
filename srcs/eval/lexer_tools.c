/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:28:34 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 15:28:36 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

void	ft_lex_backslash(t_eval *e)
{
	e->eval[e->curr++] = ' ';
	if (!(e->s[e->curr]))
	{
		e->err = B_MISS;
		e->c = '\\';
	}
	else
		e->eval[e->curr++] = 'e';
}

void	ft_lex_parenth(t_eval *e)
{
	char	c;
	int		save;

	save = e->curr;
	c = e->s[save];
	while (e->s[e->curr] && ((c == '(' && e->s[e->curr] != ')')
	|| (c == '{' && e->s[e->curr] != '}')))
	{
		e->eval[e->curr++] = 'v';
		if (e->s[e->curr] == '(' || e->s[e->curr] == '{')
			ft_lex_parenth(e);
	}
	if (!e->s[e->curr])
	{
		e->err = P_MISS;
		e->c = c;
	}
	else
		e->eval[e->curr++] = 'v';
}

void	ft_lex_var(t_eval *e)
{
	e->eval[e->curr++] = 'v';
	if (e->s[e->curr - 1] == '$')
	{
		if (ft_isparenth(e->s[e->curr]))
			ft_lex_parenth(e);
		while (e->s[e->curr] && (ft_isalpha(e->s[e->curr]) ||
		e->s[e->curr] == '_'))
			e->eval[e->curr++] = 'v';
	}
}

void	ft_lex_dquote(t_eval *e)
{
	e->eval[e->curr++] = ' ';
	while (e->s[e->curr] != 0 && e->s[e->curr] != '"')
	{
		if (e->s[e->curr] == '\\' && (e->eval[e->curr++] = 'q')
		&& e->s[e->curr + 1] == '"')
			e->eval[e->curr++] = 'q';
		else if (e->s[e->curr] == '$' || e->s[e->curr] == '~')
			ft_lex_var(e);
		else
			e->eval[e->curr++] = 'q';
	}
	if (!e->s[e->curr])
	{
		e->err = DQ_MISS;
		e->c = '"';
	}
	else
		e->eval[e->curr++] = ' ';
}

void	ft_lex_quote(t_eval *e)
{
	e->eval[e->curr++] = ' ';
	while (e->s[e->curr] != 0 && e->s[e->curr] != '\'')
		e->eval[e->curr++] = 's';
	if (!e->s[e->curr])
	{
		e->err = Q_MISS;
		e->c = '\'';
	}
	else
		e->eval[e->curr++] = ' ';
}
