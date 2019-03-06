/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:18:17 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/06 14:18:18 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

t_word			*ft_deltword(t_word *prev, t_word *src)
{
	prev->next = src->next;
	src->next = NULL;
	ft_free_tword(src);
	return (prev);
}

t_word			*new_tword(void)
{
	t_word	*n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

static t_word	*ft_cpytword(t_word *src)
{
	t_word	*new;

	if (!(new = new_tword()))
		return (NULL);
	new->type = src->type;
	if (!(new->word = ft_strdup(src->word)))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

t_word			*ft_addtword(t_word *head, t_word *new)
{
	t_word	*tmp;

	if (!new)
		return (head);
	if (!head)
		return (ft_cpytword(new));
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_cpytword(new);
	return (head);
}
