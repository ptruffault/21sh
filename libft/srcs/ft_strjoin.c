/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:19:06 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/03 16:18:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*new;
	unsigned int		count;

	count = 0;
	if (s1 && (!s2 || *s2 == 0))
		return (ft_strdup(s1));
	if ((!s1 || *s1 == 0) && s2)
		return (ft_strdup(s2));
	if ((!s1 && !s2) || !(new = (char *)malloc(sizeof(char) *
	(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
	{
		*new++ = *s1++;
		count++;
	}
	while (*s2)
	{
		*new++ = *s2++;
		count++;
	}
	*new = '\0';
	return (new - count);
}
