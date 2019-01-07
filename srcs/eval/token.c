/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parseur.h>

static t_word *find_type(t_word *w, char c, int *pos)
{
	if (c == 'o')
		w->type = OPERATEUR;
	else if (c == 'r')
		w->type = REDIRECT;
	else if (c == 'q')
		w->type = QUOTE;
	else if (c == 'v')
		w->type = VAR;
	else if (c == 'e')
	{
		if (*pos == 0)
			w->type = CMD;
		else
			w->type = PATH;
		*pos = *pos + 1;
	}
	else
		w->type = 0;
	return (w);
}



static t_word *get_next_word(t_word *w, char *eval, char *input, int *i, int *pos)
{
	char c;
	int begin;

	c = eval[*i];
	begin = *i;
	while (eval[*i] && (eval[*i] == c || (c == 'q' && eval[*i] == 'v')))
		*i = *i + 1;
	 if (!(w->word = ft_strndup(input + begin, *i - begin)))
	 	return (w);
	 return (find_type(w, c, pos));
}

static t_word *ft_get_words(char *input, char *eval)
{
	t_word *head;
	t_word *tmp;
	int pos;
	int i;
	int len;

	i = 0;
	pos = 0;
	if (!(head = new_tword()))
		return (NULL);
	len = ft_strlen(input);
	tmp = head;
	while (eval[i] == ' ')
		i++;
	while (i < len)
	{
		if (eval[i] == 0 || !(tmp = get_next_word(tmp, eval, input, &i, &pos)))
			return (head);
		if (eval[i] == 0 || !(tmp->next = new_tword()))
			return (head);
		tmp = tmp->next;
		while (eval[i] == ' ')
			i++;
	}
	return (head);
}


t_word *eval_line(char *input)
{
	t_word *head;
	t_eval e;

	if (!input|| !*input || ft_isempty(input))
		return (NULL);
	e = lexer(input);
	head = ft_get_words(e.s, e.eval);
	if (head->type == OPERATEUR || head->type == REDIRECT)
	{
		error("syntax error near", head->word);
		ft_free_tword(head);
		return (NULL);
	}
	ft_strdel(&e.eval);
	ft_strdel(&e.s);
	return (head);
}