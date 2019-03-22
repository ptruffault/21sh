/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:29:27 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:29:31 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_stradd_char(char *str, char c)
{
	char	*new;
	int		len;

	if (!(str))
	{
		if (!(str = ft_strnew(2)))
			return (NULL);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	len = ft_strlen(str);
	if (!(new = ft_strnew(len + 2)))
		return (NULL);
	new = ft_strcpy(new, str);
	new[len] = c;
	new[len + 1] = '\0';
	ft_strdel(&str);
	return (new);
}
