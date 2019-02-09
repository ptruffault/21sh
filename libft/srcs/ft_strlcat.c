/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:59:31 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 10:59:43 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest;
	size_t	source;

	dest = 0;
	source = 0;
	while (size != 0 && *(dst + dest) != '\0')
	{
		dest++;
		size--;
	}
	if (size == 0)
		return (dest + ft_strlen(src));
	while (*src != '\0')
	{
		if (size != 1)
		{
			*(dst + dest) = *src;
			dst++;
			size--;
		}
		src++;
		source++;
	}
	*(dst + dest) = '\0';
	return (dest + source);
}
