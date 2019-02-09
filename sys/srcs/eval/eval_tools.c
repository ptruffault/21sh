/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:02:47 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int			ft_twordlen(t_word *w)
{
	int	i;

	i = 0;
	while (w)
	{
		w = w->next;
		i++;
	}
	return (i);
}

t_word		*new_tword(void)
{
	t_word	*n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

t_word		*ft_cpytword(t_word *src)
{
	t_word	*new;

	if (!(new = new_tword()))
		return (NULL);
	new->type = src->type;
	new->word = ft_strdup(src->word);
	return (new);
}

char		**ft_twordto_arr(t_word *w)
{
	char	**arr;
	int		i;

	i = 0;
	if (!(w = ft_expention(w)))
		return (NULL);
	if (!(arr = malloc(sizeof(char *) * (ft_twordlen(w) + 1))))
		return (NULL);
	while (w)
	{
		if ((arr[i] = ft_strdup(w->word)))
			i++;
		w = w->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_word		*ft_addtword(t_word *head, t_word *new)
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
