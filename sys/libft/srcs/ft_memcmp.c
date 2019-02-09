/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:58:29 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 10:58:33 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*blop1;
	const unsigned char	*blop2;

	blop1 = s1;
	blop2 = s2;
	while (n > 0)
	{
		if (*blop1 != *blop2)
			return ((int)(*blop1 - *blop2));
		blop1++;
		blop2++;
		n--;
	}
	return (0);
}
