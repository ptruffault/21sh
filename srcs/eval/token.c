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



static t_word *get_next_word(t_word *w, char *eval, char *input, int *i, int *pos)
{
	char c;
	int begin;

	begin = *i;
	c = eval[*i];
	if (eval[*i] == 'o' || eval[*i] == 'r')
	{
		while (eval[*i] && eval[*i] == c)
			*i = *i + 1;
		*pos = 0;
	}
	else
	{
		while (eval[*i] && eval[*i] != ' ' && eval[*i] != 'o' && eval[*i] != 'r')
			*i = *i + 1;
	}
	 if (!(w->word = ft_strndup(input + begin, *i - begin)))
	 	return (NULL);
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
		while (eval[i] && eval[i] == ' ')
			i++;
	}
	return (head);
}

//A REFAIRE C'EST DEGEU
// BUG SUR ALIAS="ALIAS (...)" -> boucle infini qui segfault
t_word *add_alias(t_word *w, const char *alias)
{
	char *tmp_al;
	t_word *save;
	t_word *new;
	t_word *tmp;

	if ((tmp_al = ft_strdup(alias)) 
	&& (new = eval_line((tmp_al))))
	{
		save = w->next;
		ft_strdel(&w->word);
		w->word = ft_strdup(new->word);
		w->next = new->next;
		new->next = NULL;
		ft_free_tword(new);
		tmp = w;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = save;
	}
	return (w);
}

t_word *check_alias(t_word *head, t_envv *e_alias)
{
	t_word *tmp;
	char *alias;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == CMD && (alias = get_tenvv_val(e_alias, tmp->word)))
			tmp = add_alias(tmp, alias);
		tmp = tmp->next;
	}
	return (head);
}

t_word *eval_line(char *input)
{
	t_word *head;
	t_eval e;
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	if (!input|| !*input || ft_isempty(input))
		return (NULL);
	e = lexer(input);
	head = ft_get_words(e.s, e.eval);
	if (sh->alias)
		head = check_alias(head, sh->alias);
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