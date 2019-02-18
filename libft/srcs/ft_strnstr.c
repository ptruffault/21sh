/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:02:27 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/04 18:25:16 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;

	if (s2[0] == '\0')
		return ((char *)s1);
	i = ft_strlen(s2);
	while (*s1 && len-- >= i)
	{
		if (*s1 == *s2 && ft_memcmp(s1, s2, i) == 0)
			return ((char*)s1);
		s1++;
	}
	return (0);
}
