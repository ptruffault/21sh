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

t_word *get_argv(t_tree *t, t_word *w)
{
	while (w && w->word && IS_CMD(w->type))
	{
		t->cmd = ft_addtword(t->cmd, w);
		w = w->next;
	}
	return (w);
}

int find_operateur(char *op)
{
	char *operateur[4] = {
		"&&", "||", ";", "|"
	};
	int i;

	i = 0;
	while (operateur[i])
	{
		if (ft_strequ(operateur[i++], op))
			return (i);
	}
	return (0);
}

t_tree *add_newttree(t_tree *tree, t_word *w)
{
	tree->o_type = find_operateur(w->word);
	if (tree->o_type != O_SEP && (!w->next || !w->next->word))
	{
		w ->next = NULL;
		while (!w->next)
			w->next = o_get_input(tree->o_type);
	}
	if (w->type != 0)
	{
		if (!(tree->next = new_tree()))
			return (tree);
		w = w->next;
	}
	return (tree->next);
}

t_tree *get_tree(char *input)
{
	t_tree	*head;
	t_tree	*tree;
	t_word *tmp;
	t_word *w;

	if (!input || ft_isempty(input) || 
	!(w = eval_line(input)) || !(head = new_tree()))
		return (NULL);
	tree = head;
	ft_get_set_tree(head);
	tmp = w;
	while (tmp && tmp->word)
	{
		if (IS_CMD(tmp->type))
			tmp = get_argv(tree, tmp);
		else if (tmp->type == REDIRECT)
			tmp = get_redirections(tree, tmp);
		else if (tmp->type == OPERATEUR)
		{
			tree = add_newttree(tree, tmp);
			tmp = tmp->next;
		}
	}
	ft_free_tword(w);
	return (head);
}
