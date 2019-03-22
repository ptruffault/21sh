/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:28:21 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/22 15:30:38 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strnew(size_t size)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i <= size)
		new[i++] = '\0';
	return (new);
}
