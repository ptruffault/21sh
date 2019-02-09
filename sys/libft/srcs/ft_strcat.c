/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:13:36 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/22 14:54:08 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t i;
	size_t j;

	j = 0;
	i = ft_strlen(dest);
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
