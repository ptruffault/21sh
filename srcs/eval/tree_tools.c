/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:30:54 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 15:30:56 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

t_tree		*new_tree(void)
{
	t_tree	*n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->cmd = NULL;
	n->r = NULL;
	n->o_type = 0;
	n->ret = 0;
	n->next = NULL;
	return (n);
}

t_redirect	*new_redirection(void)
{
	t_redirect	*new;

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
