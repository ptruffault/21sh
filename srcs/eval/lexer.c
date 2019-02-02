/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:26:09 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/05 13:26:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parseur.h>

void ft_lex_backslash(t_eval *e)
{
	e->eval[e->curr++] = ' ';
	if (!(e->s[e->curr]))
	{
		e->s = ft_strjoin_fr(e->s, backslash_get_input());
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(e->s) + 1);
	}
	e->eval[e->curr++] = 'e';
}

void ft_lex_parenth(t_eval *e)
{
	char c;
	int save;

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
		e->s = ft_strjoin_fr(e->s , p_get_input(c));
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(e->s) + 1);
		e->curr = save;
		ft_lex_parenth(e);
	}
	else
		e->eval[e->curr++] = 'v';
}

void ft_lex_var(t_eval *e)
{
	e->eval[e->curr++] = 'v';
	if (e->s[e->curr - 1] == '$')
	{
		if (ft_isparenth(e->s[e->curr]))
			ft_lex_parenth(e);
		while(e->s[e->curr] && (ft_isalpha(e->s[e->curr]) || 
		e->s[e->curr] == '_'))
			e->eval[e->curr++] = 'v';
	}
}

void ft_lex_dquote(t_eval *e)
{

	e->eval[e->curr++] = ' ';
	while (e->s[e->curr] != 0 && e->s[e->curr] != '"')
	{
		if (e->s[e->curr] == '\\' && (e->eval[e->curr++] = 'q')
		&&	e->s[e->curr + 1] == '"')
			e->eval[e->curr++] = 'q';
		else if (e->s[e->curr] == '$' || e->s[e->curr] == '~')
			ft_lex_var(e);
		else
			e->eval[e->curr++] = 'q';
	}
	if (!e->s[e->curr])
	{
		e->s = ft_strjoin_fr(ft_stradd_char(e->s, '\n'), q_get_input('"'));
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(e->s) + 1);
		ft_lex_dquote(e);
	}
	else
		e->eval[e->curr++] = ' ';
}

void ft_lex_quote(t_eval *e)
{
	e->eval[e->curr++] = ' ';
	while (e->s[e->curr] != 0 && e->s[e->curr] != '\'')
		e->eval[e->curr++] = 's';
	if (!e->s[e->curr])
	{
		e->s = ft_strjoin_fr(ft_stradd_char(e->s, '\n'), q_get_input('\''));
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(e->s) + 1);
		ft_lex_quote(e);
	}
	else
		e->eval[e->curr++] = ' ';
}

void ft_lex_redirect(t_eval *e)
{
	int j;

	j = e->curr;
	while (j > 0 && ft_isdigit(e->s[j - 1]))
		e->eval[--j] = 'r';
	e->eval[e->curr++] = 'r';
	if (e->s[e->curr] == '&' && e->s[e->curr + 1]
	&& (ft_isdigit(e->s[e->curr + 1]) || e->s[e->curr + 1] == '-'))
	{
		e->eval[e->curr++] = 'r';
		if (e->s[e->curr] == '-')
			e->eval[e->curr++] = 'r';
		else
		{
			while (ft_isdigit(e->s[e->curr]))
				e->eval[e->curr++] = 'r';
		}
	}
}

void ft_clean_str(t_eval *e)
{
	char *ptr;

	while ((ptr = ft_strchr(e->eval, 'Q')) || (ptr = ft_strchr(e->eval, 'B'))  )
	{
		e->s = ft_delchar_n(e->s, ptr - e->eval);
		e->eval = ft_delchar_n(e->eval, ptr - e->eval);
	}
}

void ft_lexword(t_eval *e)
{
	while (ft_isspace(e->s[e->curr]))
		e->eval[e->curr++] = ' ';
	if (e->s[e->curr] == '\"')
		ft_lex_dquote(e);
	else if (e->s[e->curr] == '\'')
		ft_lex_quote(e);
	else if (e->s[e->curr] == '\\')
		ft_lex_backslash(e);
	else if (e->s[e->curr] == '&' || e->s[e->curr] == '|' || e->s[e->curr] == ';')
		e->eval[e->curr++] = 'o';
	else if (e->s[e->curr] == '$' || e->s[e->curr] == '~')
		ft_lex_var(e);
	else if (e->s[e->curr] == '>' || e->s[e->curr] == '<')
		ft_lex_redirect(e);
	else if (e->s[e->curr])
		e->eval[e->curr++] = 'e';
}


t_eval lexer(char *src)
{
	t_eval e;

	e.curr = 0;
	e.s = src;
	if (!(e.eval = ft_strnew(ft_strlen(e.s) + 1)))
		return (e);
	while (e.s[e.curr])
		ft_lexword(&e);
	e.eval[e.curr] = 0;
	ft_clean_str(&e);
	return (e);
}