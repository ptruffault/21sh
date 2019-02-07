/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:41:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/07 16:41:02 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

static t_word *ft_alias_to_tword(t_word *w, char *val)
{
	t_word *w_alias;
	t_eval  e_alias;
	t_word *tmp;

	e_alias = lexer(val);
	w_alias = ft_get_words(val, e_alias.eval);
	ft_strdel(&e_alias.eval);
	ft_strdel(&w->word);
	w->word = ft_strdup(w_alias->word);
	if (w_alias->next)
	{
		tmp = w_alias->next;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = w->next;
		w->next = w_alias->next;
	}
	w_alias->next = NULL;
	ft_free_tword(w_alias);
	return (w);
}

t_word *ft_check_alias(t_word *head ,t_shell *sh)
{
	t_word *tmp_w;
	char *val;

	tmp_w = head;
	while (tmp_w)
	{
		if (tmp_w->type == CMD && (val = get_tenvv_val(sh->alias, tmp_w->word)))
			tmp_w = ft_alias_to_tword(tmp_w, val);
		tmp_w = tmp_w->next;
	}
	return (head);
}
