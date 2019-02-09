/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:17:57 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:18:00 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnew_nchar(char c, int n)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = ft_strnew(n + 1)))
		return (NULL);
	while (i < n)
		new[i++] = c;
	new[i] = '\0';
	return (new);
}
