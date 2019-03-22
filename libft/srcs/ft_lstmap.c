/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:41:50 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/03 14:42:44 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;

	if (lst != NULL && (new = (t_list *)malloc(sizeof(t_list))))
	{
		new = f(lst);
		new->next = ft_lstmap(lst->next, f);
		return (new);
	}
	return (NULL);
}
