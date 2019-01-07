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
#include <parseur.h>

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

static int ft_find_redirect_type(char *red)
{
	char *ptr;

	 if ((ptr = ft_strchr(red, '<')))
	 	return ((*(ptr + 1) == '<' ? R_DLEFT : R_LEFT));
	 if ((ptr = ft_strchr(red, '>')))
	 	return ((*(ptr + 1) == '>' ? R_DRIGHT : R_RIGHT));
	 return (0);
}

static t_redirect *get_redirection(t_redirect *new, t_word *w)
{

	new->t = ft_find_redirect_type(w->word);
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
	while (w && w->type == REDIRECT)
	{
		if (!(tmp = get_redirection(tmp, w)))
		{
			w->type = 0;
			return (w);
		}
		else if (tmp->path && w->next && !ft_strequ(tmp->path, "/dev/null"))
			w = w->next;
		if (w && w->next && w->next->type == REDIRECT)
		{
				tmp->next = new_redirection();
				tmp = tmp->next;
		}
		w = w->next;
	}
	return (w);
}