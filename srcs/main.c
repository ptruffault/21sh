/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

// HISTORY BUG

// malloc.c:2401: sysmalloc: Assertion `(old_top == initial_top (av) && old_size =
// = 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned
// long) old_end & (pagesize - 1)) == 0)' failed.
//Aborted (core dumped)


char *get_binpath(char **input, t_envv *e, int *i)
{
	int inf;
	char *ret;

	inf = check_builtin(&input[*i]);
	if (inf == 1)
		 ret = ft_strdup(input[*i]);
	else if (inf == 0)
		 ret = check_bin(input[*i], e);
	*i = *i + 1;
	if (!ret)
		while ((input[*i]) && !IS_EOI(input[*i]) && !IS_PIPE(input[*i]))
			*i = *i + 1;
	return (ret);
}

void eval_tree(t_tree *t, char **input, t_envv *e)
{
	t_tree *tmp;
	int arr_len;
	int i;

	i = 0;
	tmp = t;
	arr_len = ft_strarrlen(input);
	while (i < arr_len)
	{
		if ((tmp->p = get_binpath(input, e, &i)))
		{
			tmp->a = get_arguments(input , &i, e);
			tmp = get_redirection(tmp, input, &i);
		}
		print_tree(tmp);
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

int		main(int argc, char **argv, char **envv)
{
	t_envv	*my_envv;
	t_tree	*t;

	if (!(my_envv = new_tenvv()))
		return (-1);
	my_envv = init_tenvv(my_envv, envv);
	while (42)
	{
		ft_disp(my_envv, argc, argv);
		if ((t = get_tree(get_input(envv), my_envv)))
			ft_free_tree(t);
	}
	return (0);
}
