/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:41:36 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static t_word	*find_type(t_word *w, char c, int *pos)
{
	if (c == 'o')
		w->type = OPERATEUR;
	else if (c == 'r')
		w->type = REDIRECT;
	else if (c == 'q')
		w->type = DQUOTE;
	else if (c == 's')
		w->type = QUOTE;
	else if (c == 'v')
		w->type = VAR;
	else if (c == 'e')
	{
		if (*pos == 0)
			w->type = CMD;
		else
			w->type = ARG;
		*pos = *pos + 1;
	}
	else
		w->type = 0;
	return (w);
}

static t_word	*g_n_w(t_word *w, t_eval *e, int *i, int *pos)
{
	char	c;
	int		begin;

	begin = *i;
	c = e->eval[*i];
	if (e->eval[*i] == 'o' || e->eval[*i] == 'r')
	{
		while (e->eval[*i] && e->eval[*i] == c)
			*i = *i + 1;
		*pos = 0;
	}
	else
	{
		while (e->eval[*i] && e->eval[*i] != ' '
				&& e->eval[*i] != 'o' && e->eval[*i] != 'r')
			*i = *i + 1;
	}
	if (!(w->word = ft_strndup(e->s + begin, *i - begin)))
		return (NULL);
	return (find_type(w, c, pos));
}

t_word			*ft_get_words(t_eval *e)
{
	t_word	*head;
	t_word	*tmp_w;
	int		pos;
	int		i;
	int		len;

	i = 0;
	pos = 0;
	if (!(head = new_tword()))
		return (NULL);
	len = ft_strlen(e->s);
	tmp_w = head;
	while (e->eval[i] == ' ')
		i++;
	while (i < len)
	{
		if (e->eval[i] == 0 || !(tmp_w = g_n_w(tmp_w, e, &i, &pos)))
			return (head);
		if (e->eval[i] == 0 || !(tmp_w->next = new_tword()))
			return (head);
		tmp_w = tmp_w->next;
		while (e->eval[i] && e->eval[i] == ' ')
			i++;
	}
	return (head);
}

t_word			*eval_line(char *input)
{
	t_word	*head;
	t_eval	e;
	t_shell	*sh;

	sh = ft_get_set_shell(NULL);
	if (!input || !*input || ft_isempty(input))
		return (NULL);
	e = lexer(input);
	head = ft_get_words(&e);
	ft_check_alias(head, sh);
	ft_strdel(&e.eval);
	ft_strdel(&e.s);
	if (head->type == OPERATEUR)
	{
		error("syntax error near", head->word);
		ft_free_tword(head);
		return (NULL);
	}
	return (head);
}
