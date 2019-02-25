/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:27:14 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/03 16:11:05 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	i2;

	if (s == NULL || len == 0)
		return (NULL);
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = 0;
	i2 = 0;
	i2 += start;
	while (i < len && s[i2])
		new[i++] = s[i2++];
	return (new);
}
