/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:18:17 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

t_word			*ft_deltword(t_word *prev, t_word *src)
{
	if (src && prev)
	{
		prev->next = src->next;
		src->next = NULL;
		src = ft_free_tword(src);
	}
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
	t_word	*ret;

	if (!(ret = new_tword()))
		return (NULL);
	ret->type = src->type;
	if (!(ret->word = ft_strdup(src->word)))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_word			*ft_addtword(t_word *head, t_word *ret)
{
	t_word	*tmp;

	if (!ret)
		return (head);
	if (!head)
		return (ft_cpytword(ret));
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_cpytword(ret);
	return (head);
}
