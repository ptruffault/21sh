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
#include "../includes/21sh.h"

static t_redirect *new_redirection(void)
{
	t_redirect *new;

	if (!(new = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	new->t = 0;
	new->to = -2;
	new->from = -1;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

static t_redirect *get_redirection(t_redirect *new, t_word *w)
{
	char *ptr;

	new->t = w->type;
	if (new->t == R_RIGHT)
	{
		new->from = (ft_isdigit(w->word[0]) ? ft_atoi(w->word) : 1);
		if ((ptr = ft_strchr(w->word, '&')) && (ft_isdigit(*(ptr + 1)) || *(ptr + 1) == '-'))
			new->to = (ft_isdigit(*(ptr + 1)) ? ft_atoi(ptr + 1) : -1);
	}
	else {
		new->to = 0;
		new->from = -1;
	}
	if (w->next && ((new->to == -2 && (new->t == R_RIGHT || new->t == R_DRIGHT))
	 || (new->from == -1 && (new->t == R_LEFT || new->t == R_DLEFT))))
	{
		w = w->next;
		new->path = ft_strdup(w->word);
	}
	else if (new->to == -2)
	{
		warning("redirection need an argument", "[ >(>) / <(<) ] [&Y / file_path]");
		new = NULL;
	}
	return (new);
}

static t_word *get_redirections(t_tree *t, t_word *w)
{
	t_redirect *tmp;

	t->r = new_redirection();
	tmp = t->r;
	while (w && IS_REDIRECTION(w->type))
	{
		tmp = get_redirection(tmp, w);
		if (tmp->path && w->next)
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

t_word *get_argv(t_tree *t, t_word *w)
{
	int argc;
	int i;
	t_word *tmp;

	argc = 0;
	i = 0;
	tmp = w;
	while (tmp && IS_CMD(tmp->type) && ++argc > 0)
		tmp = tmp->next;
	if (argc == 0 || !(t->arr = (char **)malloc(sizeof(char *) * (argc + 1))))
		return (NULL);
	while (w && IS_CMD(w->type))
	{
		t->arr[i++] = ft_strdup(w->word);
		w = w->next;
	}
	t->arr[i] = NULL;
	return (w);
}

t_tree *get_tree(char *input)
{
	t_tree	*head;
	t_tree	*tree;
	t_word *tmp;
	t_word *w;

	w = eval_line(input);
	ft_strdel(&input);
	if (!(head = new_tree()))
		return (head);
	tree = head;
	tmp = w;
	while (tmp && tmp->word)
	{
		if (IS_CMD(tmp->type))
			tmp = get_argv(tree, tmp);
		else if (IS_REDIRECTION(tmp->type))
			tmp = get_redirections(tree, tmp);
		else if (IS_OPERATEUR(tmp->type) && (tmp->next || ft_strequ(tmp->word, ";")))
		{
			if (!(tree->next = new_tree()))
				return (head);
			tree->o_type = tmp->type;
			tmp = tmp->next;
			tree = tree->next;
		}
		else
		{
			error("parse error near", tmp->word);
			break ;
		}
	}
	ft_free_tword(w);
	return (head);
}
