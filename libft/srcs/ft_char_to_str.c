/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:55:07 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:55:17 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_char_to_str(char c)
{
	char *new;

	if (!(new = ft_strnew(2)))
		return (NULL);
	new[0] = c;
	new[1] = '\0';
	return (new);
}
