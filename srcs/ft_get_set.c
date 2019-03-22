/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:18:04 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

t_shell	*ft_get_set_shell(t_shell *sh)
{
	static t_shell *s = NULL;

	if (sh != NULL)
		s = sh;
	return (s);
}

t_tree	*ft_get_set_tree(t_tree *new_t)
{
	static t_tree	*stored_t = NULL;

	if (new_t)
		stored_t = new_t;
	return (stored_t);
}
