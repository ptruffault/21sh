/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:15:16 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static t_word	*get_argv(t_tree *t, t_word *w)
{
	while (w && w->word && IS_CMD(w->type))
	{
		t->cmd = ft_addtword(t->cmd, w);
		w = w->next;
	}
	return (w);
}

static t_tree	*ft_syntax(t_tree *t, t_word *w)
{
	error("syntax error", t->cmd->word);
	ft_free_tree(t);
	ft_free_tword(w);
	return (NULL);
}

static t_tree	*built_tree(t_tree *head, t_word *w)
{
	t_word	*tmp;
	t_tree	*tree;

	tmp = w;
	tree = head;
	while (tmp && tmp->word)
	{
		if (tmp && IS_CMD(tmp->type))
			tmp = get_argv(tree, tmp);
		else if (tmp && tmp->type == REDIRECT)
		{
			if (!(tmp = get_redirections(tree, tmp)))
				return (ft_syntax(head, w));
			tmp = tmp->next;
		}
		else if (tmp && tmp->type == OPERATEUR)
		{
			tree = add_newttree(tree, tmp);
			tmp = tmp->next;
		}
	}
	return (head);
}

t_tree			*get_tree(char *input)
{
	t_tree	*head;
	t_word	*w;

	if (!input || ft_isempty(input) || !ft_check_ascii(input) ||
	!(w = eval_line(input)))
		return (NULL);
	if (!(head = new_tree()))
		return (NULL);
	head = built_tree(head, w);
	ft_free_tword(w);
	ft_get_set_tree(head);
	return (head);
}
