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

#include <21sh.h>

void ft_parse_backslash(t_eval *e)
{

	if (e->s[e->curr + 1])
	{
		e->s = ft_delchar_n(e->s, e->curr);
		if (e->status == S_DQUOTE)
		{
			e->eval[e->curr] = 'q';
			if (e->s[e->curr] == 'n')
				e->s[e->curr] = '\n';
			else if (e->s[e->curr] == 't')
				e->s[e->curr] = '\t';
			else if (e->s[e->curr] == 'f')
				e->s[e->curr] = '\f';
			else if (e->s[e->curr] == 'a')
				e->s[e->curr] = '\a';
			else if (e->s[e->curr] == 'b')
				e->s[e->curr] = '\b';
			else if (e->s[e->curr] == 'r')
				e->s[e->curr] = '\r';
			else if (e->s[e->curr] == 'v')
				e->s[e->curr] = '\v';
		}
		else
			e->eval[e->curr] = 'e';
	}
	else
	{
		e->s = ft_strjoin_fr(e->s, backslash_get_input());
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(e->s) + 1);
		ft_parse_backslash(e);
	}
}

void ft_parse_var(t_eval *e)
{
	char *name;
	char *value;
	char *ret;
	int len;

	len = 1;

	if (e->s[e->curr] == '$')
	{
		while (e->s[e->curr + len] && e->s[e->curr + len] != '"' && !ft_isspace(e->s[e->curr + len])
		&& e->s[e->curr + len] != '$' && e->s[e->curr + len] != '\\')
			len++;
		name = ft_strsub(e->s, e->curr + 1, len - 1);
	}
	else if (e->s[e->curr] == '~')
		name = ft_strdup("HOME");
	if (name)
	{
		value = ft_strdup(get_tenvv_val(ft_get_set_envv(NULL), name));
		ret = ft_strpull(e->s, &e->s[e->curr] , len - 1, value);
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(ret) + 1);
		ft_strdel(&name);
		ft_strdel(&e->s);
		ft_strdel(&value);
		e->s = ret;
	}
}


void ft_lex_dquote(t_eval *e)
{
	if (e->s[e->curr] == '"')
		e->eval[e->curr++] = 'Q';
	while (e->s[e->curr] != 0 && e->s[e->curr] != '"')
	{
		if (e->s[e->curr] == '\\')
			ft_parse_backslash(e);
		else if (e->s[e->curr] == '$')
			ft_parse_var(e);
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
		e->eval[e->curr] = 'Q';
}

void ft_lex_quote(t_eval *e)
{
	if (e->s[e->curr] == '\'')
		e->eval[e->curr++] = 'Q';
	while (e->s[e->curr] != 0 && e->s[e->curr] != '\'')
		e->eval[e->curr++] = 'q';
	if (!e->s[e->curr])
	{
		e->s = ft_strjoin_fr(ft_stradd_char(e->s, '\n'), q_get_input('\''));
		e->eval = ft_realloc(e->eval, ft_strlen(e->eval) + 1, ft_strlen(e->s) + 1);
		ft_lex_quote(e);
	}
	else
		e->eval[e->curr] = 'Q';
}

void ft_lex_right_redirect(t_eval *e)
{
	int j;
	int len;

	len = ft_strlen(e->s);
	j = e->curr;
	while (j > 0 && ft_isdigit(e->s[j - 1]))
		e->eval[--j] = 'r';
	e->eval[e->curr] = 'r';
	if (e->curr + 2 < len && e->s[e->curr + 1] == '&')
	{
		e->eval[++e->curr] = 'r';
		if (e->s[e->curr + 1] == '-' && (!e->s[e->curr + 2] || ft_isspace(e->s[e->curr + 2])))
			e->eval[++e->curr] = 'r';
		else
		{
			while (ft_isdigit(e->s[e->curr + 1]))
				e->eval[++e->curr] = 'r';
		}
	}
}

void ft_clean_quote(t_eval *e)
{
	char *ptr;

	if ((ptr = ft_strchr(e->eval, 'Q')))
	{
		e->s = ft_delchar_n(e->s, ptr - e->eval);
		e->eval = ft_delchar_n(e->eval, ptr - e->eval);
	}
}

void ft_lex_quotes(t_eval *e)
{
	if (e->status == S_QUOTE)
		ft_lex_quote(e);
	else if (e->status == S_DQUOTE)
		ft_lex_dquote(e);
	ft_clean_quote(e);
	ft_clean_quote(e);
	e->curr--;
}	


void ft_lexword(t_eval *e)
{
	int word_over;

	word_over = 0;
	while (word_over == 0)
	{

		if (e->status == S_QUOTE || e->status == S_DQUOTE)
		{
			ft_lex_quotes(e);
			break ;
		}
		else if (e->status == S_VAR)
		{
			ft_parse_var(e);
			break ;
		}
		else if (e->status == 0)
		{
			
			if (e->s[e->curr] == '\\')
				ft_parse_backslash(e);
			else if (e->s[e->curr] == '&' || e->s[e->curr] == '|' || e->s[e->curr] == ';')
				e->eval[e->curr] = 'o';
			else if (e->s[e->curr] == '<')
				e->eval[e->curr] = 'r';
			else if (e->s[e->curr] == '>')
				ft_lex_right_redirect(e);
			else
				e->eval[e->curr] = 'e';
		}
		e->curr++;
		if (((ft_isspace(e->s[e->curr]) || !e->s[e->curr]) && e->status != S_QUOTE && e->status != S_DQUOTE)
		|| ((e->s[e->curr] == '$' || e->s[e->curr] == '~') && e->status != S_QUOTE))
			word_over = 1;
	}
}


t_eval lexer(char *src)
{
	t_eval e;

	e.curr = 0;
	e.status = 0;
	e.s = src;
	if (!(e.eval = ft_strnew(ft_strlen(e.s) + 1)))
		return (e);
	while (e.s[e.curr])
	{
		while (ft_isspace(e.s[e.curr]))
			e.eval[e.curr++] = ' ';
		if (e.s[e.curr] == '\'' || e.s[e.curr] == '\"')
			e.status = (e.s[e.curr] == '\"' ? S_DQUOTE : S_QUOTE);
		else if (e.s[e.curr] == '$' ||  (e.s[e.curr] == '~'))
			e.status = S_VAR;
		else
			e.status = 0;
		ft_lexword(&e);
	}
	e.eval[e.curr] = 0;
	ft_putendl(e.eval);
	return (e);
}