/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 13:12:48 by adi-rosa         ###   ########.fr       */
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

static t_tree	*ft_syntax(t_tree *t)
{
	error("syntax error", NULL);
	ft_free_tree(t);
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
				return (ft_syntax(head));
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

int				ft_check_grammar(t_word *w)
{
	int cmd;

	cmd = 0;
	while (w)
	{
		if (w->type == OPERATEUR && w->next && w->next->type == OPERATEUR)
		{
			error("syntax error near", w->word);
			return (0);
		}
		if (IS_CMD(w->type))
			cmd++;
		w = w->next;
	}
	if (!cmd)
	{
		warning("nothing to do", NULL);
		return (0);
	}
	return (1);
}

t_tree			*get_tree(char *input)
{
	t_tree	*head;
	t_word	*w;

	if (!input || ft_isempty(input) || !ft_check_ascii(input)
	|| !(w = eval_line(input)))
		return (NULL);
	if (!(head = new_tree()))
		return (NULL);
	if (ft_check_grammar(w) && (head = built_tree(head, w)))
		ft_get_set_tree(head);
	ft_free_tword(w);
	return (head);
}
