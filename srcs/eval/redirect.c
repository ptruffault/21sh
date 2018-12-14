/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:20:36 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <21sh.h>

static t_redirect *parse_right_redirect(t_redirect *new, t_word *w)
{
	char *ptr;

	new->from = (ft_isdigit(w->word[0]) ? ft_atoi(w->word) : 1);
	if ((ptr = ft_strchr(w->word, '&'))) 
	{
		if (ft_isdigit(*(ptr + 1)))
			new->to = ft_atoi(ptr + 1);
		if (*(ptr + 1) == '-')
			new->path = ft_strdup("/dev/null");
	}
	else if (w->next && w->next->word)
		new->path = ft_strdup(w->next->word);
	else

		return (NULL);
	return (new);
}

static t_redirect *parse_left_redirect(t_redirect *new, t_word *w)
{


	new->from = STDIN_FILENO;
	if (new->t == R_DLEFT)
	{
		if (w->next && w->next->word)
		{
			new->path = ft_strdup(w->next->word);
			new->heredoc = heredoc_get_input(new->path);
		}
		else
			return (NULL);
	}
	else if (w->next && w->next->word)
		new->path = ft_strdup(w->next->word);
	else
		return (NULL);
	return (new);
}

static t_redirect *get_redirection(t_redirect *new, t_word *w)
{

	new->t = w->type;
	new->to = -2;
	if (((new->t == R_RIGHT || new->t == R_DRIGHT) && !(new = parse_right_redirect(new, w)))
	|| ((new->t == R_LEFT || new->t == R_DLEFT) && !(new = parse_left_redirect(new, w))))
	{
		error("invalid redirection", "argument needed");
		return (NULL);
	}
	return (new);
}

t_word *get_redirections(t_tree *t, t_word *w)
{
	t_redirect *tmp;

	t->r = new_redirection();
	tmp = t->r;
	while (w && IS_REDIRECTION(w->type))
	{
		if (!(tmp = get_redirection(tmp, w)))
		{
			w->type = 0;
			return (w);
		}
		else if (tmp->path && w->next)
			w = w->next;
		if (w && w->next && IS_REDIRECTION(w->next->type))
		{
				tmp->next = new_redirection();
				tmp = tmp->next;
		}
		w = w->next;
	}
	return (w);
}