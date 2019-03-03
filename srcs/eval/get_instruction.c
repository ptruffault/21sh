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

static int		find_operateur(char *op)
{
	char	*operateur[5];
	int		i;

	operateur[0] = "&&";
	operateur[1] = "||";
	operateur[2] = ";";
	operateur[3] = "|";
	operateur[4] = "&";
	i = 0;
	while (i < 5)
		if (ft_strequ(operateur[i++], op))
			return (i);
	return (0);
}

static t_tree	*add_newttree(t_tree *tree, t_word *w)
{
	tree->o_type = find_operateur(w->word);
	if (w->type != 0)
	{
		if (!(tree->next = new_tree()))
			return (tree);
		w = w->next;
	}
	return (tree->next);
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
			{
				error("invalid redirection syntax", NULL);
				ft_free_tree(head);
				return (NULL);
			}
			else
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

	if (!input || ft_isempty(input) ||
	!(w = eval_line(input)))
		return (NULL);
	if (!(head = new_tree()))
		return (NULL);
	head = built_tree(head, w);
	ft_free_tword(w);
	return (head);
}
