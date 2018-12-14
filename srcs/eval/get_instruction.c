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
		else if (IS_OPERATEUR(tmp->type))
		{
			if (!ft_strequ(tmp->word, ";") && (!tmp->next || !tmp->next->word))
			{
				tmp ->next = NULL;
				while (!tmp->next)
					tmp->next = o_get_input(tmp->type);
			}
				if (!(tree->next = new_tree()))
					return (head);
				tree->o_type = tmp->type;
				tmp = tmp->next;
				tree = tree->next;
		}
		else
		{
			error("parse error near", tmp->word);
			ft_free_tree(head);
			ft_free_tword(w);
			return (NULL);
		}
	}
	ft_free_tword(w);
	return (head);
}
