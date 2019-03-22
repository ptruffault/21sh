/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static t_redirect	*parse_right_redirect(t_redirect *ret, t_word *w)
{
	char	*ptr;

	ret->from = (ft_isdigit(w->word[0]) ? ft_atoi(w->word) : 1);
	if ((ptr = ft_strchr(w->word, '&')))
	{
		if (ft_isdigit(*(ptr + 1)))
			ret->to = ft_atoi(ptr + 1);
		else if (*(ptr + 1) == '-')
			ret->to = -1;
		return (ret);
	}
	else if (w->next && w->next->word
		&& (ret->path = ft_strdup(w->next->word)))
		return (ret);
	return (ft_free_redirection(ret));
}

static t_redirect	*parse_left_redirect(t_redirect *ret, t_word *w)
{
	char	*ptr;

	ret->from = STDIN_FILENO;
	if (ret->t == R_DLEFT)
		return (parse_heredoc(ret, w));
	else if ((ptr = ft_strchr(w->word, '&')) && ft_isdigit(*(ptr + 1)))
		ret->to = ft_atoi(ptr + 1);
	else if ((ptr = ft_strchr(w->word, '&')) && *(ptr + 1) == '-')
		ret->to = -1;
	else if (!(w->next && w->next->word
	&& (ret->path = ft_strdup(w->next->word))))
		return (ft_free_redirection(ret));
	return (ret);
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
	t_redirect *ret;

	ret = NULL;
	if ((ret = new_redirection()))
	{
		ret->t = ft_find_redirect_type(w->word);
		if (((ret->t == R_RIGHT || ret->t == R_DRIGHT)
			&& !(ret = parse_right_redirect(ret, w)))
			|| ((ret->t == R_LEFT || ret->t == R_DLEFT)
			&& !(ret = parse_left_redirect(ret, w))))
		{
			warning("redirections need an argument", w->word);
			return (NULL);
		}
	}
	return (ret);
}

t_word				*get_redirections(t_tree *t, t_word *w)
{
	t_redirect	*tmp;
	t_redirect	*ret;

	ret = NULL;
	if ((ret = get_redirection(w)))
	{
		if (ret->path)
			w = ft_deltword(w, w->next);
		if (t->r)
		{
			tmp = t->r;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = ret;
		}
		else
			t->r = ret;
		return (w);
	}
	return (NULL);
}
