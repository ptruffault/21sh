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

static t_word	*get_argv(t_tree *t, t_word *w)
{
	while (w && w->word && IS_CMD(w->type))
	{
		t->cmd = ft_addtword(t->cmd, w);
		w = w->next;
	}
	return (w);
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
		if (tmp && ((tmp->type == REDIRECT
			&& !(tmp = get_redirections(tree, tmp)))
			|| (tmp->type == OPERATEUR && !(tree = add_newttree(tree, tmp)))))
		{
			error("syntax error", NULL);
			return (ft_free_tree(head));
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (head);
}

static int		ft_check_grammar(t_word *w)
{
	int cmd;

	cmd = 0;
	while (w)
	{
		if ((w->type == OPERATEUR && w->next && w->next->type == OPERATEUR)
			|| (w->type == OPERATEUR && ft_strlen(w->word) > 2)
			|| (w->type == OPERATEUR && *w->word == ';'
			&& ft_strlen(w->word) > 1) || (w->type == REDIRECT
			&& ft_strchr(w->word, '<') && ft_strchr(w->word, '>')))
			return (error("syntax error near", w->word));
		if (IS_CMD(w->type))
			cmd++;
		w = w->next;
	}
	if (!cmd)
		return (warning("nothing to do", NULL));
	return (1);
}

int				ft_check_redirect(t_tree *t)
{
	while (t)
	{
		if (t->r && !t->cmd)
			return (error("useless redirect", NULL));
		t = t->next;
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
	{
		if (!ft_check_redirect(head))
		{
			ft_free_tword(w);
			return (ft_free_tree(head));
		}
		ft_get_set_tree(head);
	}
	w = ft_free_tword(w);
	return (head);
}
