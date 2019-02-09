/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:52:54 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 11:52:58 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t		i;
	char		*dest2;
	const char	*src2;

	dest2 = s1;
	src2 = s2;
	i = 0;
	while (n > i)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest2);
}
