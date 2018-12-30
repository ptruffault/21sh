/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parseur.h>


t_word *new_tword(void)
{
	t_word *n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

t_tree *new_tree(void)
{
	t_tree *n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->arr = NULL;
	n->r = NULL;
	n->o_type = 0;
	n->ret = 0;
	n->next = NULL;
	return (n);
}

t_redirect *new_redirection(void)
{
	t_redirect *new;

	if (!(new = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	new->t = 0;
	new->to = -2;
	new->from = -1;
	new->path = NULL;
	new->done = 0;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}