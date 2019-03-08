/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:15:39 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:15:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpull(char *src, char *ptr, int len, char *value)
{
	char *p1;
	char *p2;

	if (src - ptr == 0)
		return (ft_strjoin(value, src + len + 1));
	if (ptr - src > 0)
	{
		p1 = ft_strndup(src, ptr - src);
		p2 = ft_strjoin(value, ptr + len + 1);
		return (ft_strjoin_fr(p1, p2));
	}
	return (NULL);
}
