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

static void	find_type(char *s, t_tree *t)
{
	char *ptr;

	if ((ptr = ft_strchr(s, '>')))
		t->r.t = (*(ptr + 1) == '>' ? DR : R);
	else if ((ptr = ft_strchr(s, '<')))
		t->r.t = (*(ptr + 1) == '<' ? DL : L);
	else
		t->r.t = UK;
}	

static t_tree *get_redirection(t_tree *t ,char **input, int *i)
{
	char *ptr;

	find_type(input[*i], t);
	t->r.s = ft_strdup(input[*i]);
	*i = *i + 1;
	if (t->r.t == R || t->r.t == DR)
	{
		t->r.from = (ft_isdigit(*t->r.s) ? ft_atoi(t->r.s) : 1);
		if ((ptr = ft_strchr(t->r.s, '&')) && (ft_isdigit(*(ptr + 1)) || *(ptr + 1) == '-'))
			t->r.to = (ft_isdigit(*(ptr + 1)) ? ft_atoi(ptr + 1) : -1);
	}
	if (input[*i] &&  t->r.to == -2 && 
	(t->r.t == L || ((t->r.t == R || t->r.t == DR))))
	{
		t->r.path = ft_strdup(input[*i]);
		*i = *i + 1;
	}
	else if (t->r.to == -2)
	{
		warning("redirection need an argument", ">[&Y] [file]");
		ft_strdel(&t->r.s);
	}
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
		if ((tmp->arr = get_cmd_and_arg(input, e, &i)) &&
		IS_RED(input[i]))	
			tmp = get_redirection(tmp, input, &i);
		if (!tmp->arr)
			error("command not found", *input);
		print_tree(tmp);
		if (t->l && (tmp->next))
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
