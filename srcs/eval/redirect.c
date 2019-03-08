/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 13:16:23 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static t_redirect	*parse_right_redirect(t_redirect *new, t_word *w)
{
	char	*ptr;

	new->from = (ft_isdigit(w->word[0]) ? ft_atoi(w->word) : 1);
	if ((ptr = ft_strchr(w->word, '&')))
	{
		if (ft_isdigit(*(ptr + 1)))
			new->to = ft_atoi(ptr + 1);
		else if (*(ptr + 1) == '-')
			new->to = -1;
		return (new);
	}
	else if (w->next && w->next->word
	&& (new->path = ft_strdup(w->next->word)))
		return (new);
	ft_free_redirection(new);
	return (NULL);
}

static t_redirect	*parse_left_redirect(t_redirect *new, t_word *w)
{
	char	*ptr;

	new->from = STDIN_FILENO;
	if (new->t == R_DLEFT)
		return (parse_heredoc(new, w));
	else if ((ptr = ft_strchr(w->word, '&')) && ft_isdigit(*(ptr + 1)))
		new->to = ft_atoi(ptr + 1);
	else if ((ptr = ft_strchr(w->word, '&')) && *(ptr + 1) == '-')
		new->to = -1;
	else if (w->next && w->next->word)
		new->path = ft_strdup(w->next->word);
	else
	{
		ft_free_redirection(new);
		return (NULL);
	}
	return (new);
}

static int			ft_find_redirect_type(char *red)
{
	char	*ptr;

	if ((ptr = ft_strchr(red, '<')))
		return ((*(ptr + 1) == '<' ? R_DLEFT : R_LEFT));
	if ((ptr = ft_strchr(red, '>')))
		return ((*(ptr + 1) == '>' ? R_DRIGHT : R_RIGHT));
	return (0);
}

static t_redirect	*get_redirection(t_word *w)
{
	t_redirect *new;

	if ((new = new_redirection()))
	{
		new->t = ft_find_redirect_type(w->word);
		if (((new->t == R_RIGHT || new->t == R_DRIGHT)
		&& !(new = parse_right_redirect(new, w)))
		|| ((new->t == R_LEFT || new->t == R_DLEFT)
		&& !(new = parse_left_redirect(new, w))))
		{
			warning("redirections need an argument", w->word);
			return (NULL);
		}
	}
	return (new);
}

t_word				*get_redirections(t_tree *t, t_word *w)
{
	t_redirect	*tmp;
	t_redirect	*new;

	if ((new = get_redirection(w)))
	{
		if (new->path)
			w = ft_deltword(w, w->next);
		if (t->r)
		{
			tmp = t->r;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			t->r = new;
		return (w);
	}
	return (NULL);
}
