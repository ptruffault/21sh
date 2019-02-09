/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:00:02 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 11:21:57 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *tampon, int car, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)tampon;
	i = 0;
	while (i < n)
		str[i++] = (unsigned char)car;
	return (str);
}
