/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:41:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static t_word	*ft_next_alias(t_word *w, t_word *w_alias)
{
	t_word	*tmp;
	char	*save;

	save = w->word;
	if (!(w->word = ft_strdup(w_alias->word)))
		w->word = save;
	else
		ft_strdel(&save);
	if (w_alias->next)
	{
		tmp = w_alias->next;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = w->next;
		w->next = w_alias->next;
	}
	w_alias->next = NULL;
	ft_free_tword(w_alias);
	return (w);
}

static t_word	*ft_alias_to_tword(t_word *w, char *val)
{
	t_word	*w_alias;
	t_eval	e_alias;

	w_alias = NULL;
	lexer(&e_alias, val);
	if (e_alias.s && e_alias.eval)
		w_alias = ft_get_words(&e_alias);
	ft_strdel(&e_alias.eval);
	ft_strdel(&e_alias.s);
	if (w_alias == NULL)
		return (w);
	return (ft_next_alias(w, w_alias));
}

t_word			*ft_check_alias(t_word *head, t_shell *sh)
{
	t_word	*tmp_w;
	char	*val;
	int		i;

	tmp_w = head;
	i = 1;
	while (tmp_w)
	{
		if (tmp_w->type == OPERATEUR)
			i = 0;
		if (i == 1 && tmp_w && IS_CMD(tmp_w->type) && tmp_w->type != QUOTE
			&& (val = get_tenvv_val(sh->alias, tmp_w->word)))
			tmp_w = ft_alias_to_tword(tmp_w, val);
		else
			tmp_w = tmp_w->next;
		i++;
	}
	return (head);
}
