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

static t_tree *get_redirection(t_tree *t ,char **input, int *i)
{
	char *ptr;

	if (!(input[*i]) || !(ptr = ft_strchr(input[*i], '>')))
		return (t);
	t->r = ft_strdup(input[*i]);
	if (*(ptr + 1) == 0 || (*(ptr + 1) == '>' && *(ptr + 2) == 0))
	{
		if (!input[*i + 1])
		{
			warning("redirection need an argument", ">[&Y] [file]");
			ft_strdel(&t->r);
		}
		else
		{
			*i = *i + 1;
			t->r_path = ft_strdup(input[*i]);
		}
	}
	*i = *i + 1;
	return (t);
}

static t_tree *init_tree(char **input)
{
	t_tree *head;
	t_tree *t;
	int i;

	i = 1;
	if (!(head = new_tree()))
		return (NULL);
	t = head;
	while (input[i])
	{
		if (IS_PIPE(input[i]) || IS_EOI(input[i]))
		{
			t->l = (IS_PIPE(input[i]) ? '|' : ';');
			t->next = new_tree();
			t = t->next;
		}
		i++;
	}
	return (head);
}

static void eval_tree(t_tree *t, char **input, t_envv *e)
{
	t_tree *tmp;
	int arr_len;
	int i;

	i = 0;
	tmp = t;
	arr_len = ft_strarrlen(input);
	while (i < arr_len)
	{
		if ((tmp->arr = get_cmd_and_arg(input, e, &i)))
			tmp = get_redirection(tmp, input, &i);
		else
			error("command not found", *input);
		if (t->l &&  (tmp->next))
		{
			tmp = tmp->next;
			i++;
		}
	}
}

t_tree *get_tree(char *input, t_envv *e)
{
	t_tree	*tree;
	char 	**t;

	if (!(input = correct_syntax(input)))
		return (NULL);
	t = ft_correct(ft_strsplit_word(input), e);
	ft_strdel(&input);
	if ((tree = init_tree(t)))
		eval_tree(tree, t, e);
	ft_freestrarr(t);
	return (tree);
}
