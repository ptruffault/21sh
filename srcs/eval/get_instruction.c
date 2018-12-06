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

static void	find_type(char *s, t_redirect *r)
{
	char *ptr;

	if ((ptr = ft_strchr(s, '>')))
		r->t = (*(ptr + 1) == '>' ? 1 : 0);
	else if ((ptr = ft_strchr(s, '<')))
		r->t = (*(ptr + 1) == '<' ? 3 : 2);
	else
		r->t = -1;
}	



static t_redirect *new_redirection(void)
{
	t_redirect *new;

	if (!(new = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	new->t = -1;
	new->to = -2;
	new->from = -1;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

// a refaire adapté a une liste chainee

static t_redirect *get_redirection(t_redirect *new, char **input, int *i)
{
	char *ptr;

	find_type(input[*i], new);
	if (new->t == 0 || new->t == 1)
	{
		new->from = (ft_isdigit(*input[*i]) ? ft_atoi(input[*i]) : 1);
		if ((ptr = ft_strchr(input[*i], '&')) && (ft_isdigit(*(ptr + 1)) || *(ptr + 1) == '-'))
			new->to = (ft_isdigit(*(ptr + 1)) ? ft_atoi(ptr + 1) : -1);
	}
	else {
		new->to = 0;
		new->from = -1;
	}
	if (input[++(*i)] &&  ((new->to == -2 && (new->t == 0 || new->t == 1))
	 || (new->from == -1 && (new->t == 2 || new->t == 3))))
	{
		new->path = ft_strdup(input[*i]);
		*i = *i + 1;
	}
	else if (new->to == -2)
	{
		warning("redirection need an argument", "[ >(>) / <(<) ] [&Y / file_path]");
		new = NULL;
	}
	return (new);
}

static t_redirect *get_redirections(t_redirect *head, char **input, int *i)
{
	t_redirect *tmp;

	head = get_redirection(head, input, i);
	tmp = head;
	while (IS_RED(input[*i]))
	{
		tmp->next = new_redirection();
		tmp = get_redirection(tmp->next, input, i);
	}
	return (head);
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
		if (IS_RED(input[i]))
		{
			t->r = new_redirection();
			t->r = get_redirections(t->r, input, &i);
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
	int s;

	i = 0;
	tmp = t;
	arr_len = ft_strarrlen(input);
	while (i < arr_len)
	{
		s = i;
		if (!(tmp->arr = get_cmd_and_arg(input, e, &i)))
			error("command not found", input[s]);
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
