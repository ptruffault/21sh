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

	head = new_redirection();
	head = get_redirection(head, input, i);
	tmp = head;
	while (IS_RED(input[*i]))
	{
		tmp->next = new_redirection();
		tmp = get_redirection(tmp->next, input, i);
	}
	return (head);
}

static char ft_link(char *s)
{
	if (IS_OR(s))
		return ('o');
	else
		return (*s);
}

static t_tree *init_tree(char **input, t_envv *e)
{
	t_tree *head;
	t_tree *t;
	int i;

	i = 0;
	if (!(head = new_tree()))
		return (NULL);
	t = head;
	while (input[i])
	{
		if (!IS_SYNTAX(input[i]))
			t->arr = get_cmd_and_arg(input, e, &i);
		else if (input[i] && IS_RED(input[i]))
			t->r = get_redirections(t->r, input, &i);
		else if (input[i] && (IS_PIPE(input[i]) || IS_EOI(input[i]) || IS_OPERATEUR(input[i])))
		{
			t->l = ft_link(input[i]);
			t->next = new_tree();
			t = t->next;
			i++;
		}
	}
	return (head);
}


t_tree *get_tree(char *input, t_envv *e)
{
	t_tree	*tree;
	char 	**t;

	if (!(input = correct_syntax(input)))
		return (NULL);
	t = ft_correct(ft_strsplit_word(input), e);
	ft_strdel(&input);
	if (!(tree = init_tree(t, e)))
		error("init tree failed", NULL);
	print_tree(tree);
	ft_freestrarr(t);
	return (tree);
}
