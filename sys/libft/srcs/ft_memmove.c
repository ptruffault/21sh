/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:12:26 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 13:16:15 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*a;
	char	*b;

	a = (char *)dest;
	b = (char *)src;
	if (src <= dest)
	{
		while (len)
		{
			*(a + len - 1) = *(b + len - 1);
			len--;
		}
	}
	else
		ft_memcpy(a, b, len);
	return (dest);
}
