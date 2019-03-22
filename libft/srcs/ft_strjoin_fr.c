/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:20:57 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:21:37 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin_fr(char *s1, char *s2)
{
	char *ret;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (s2);
	if (s1 && !s2)
		return (s1);
	if (!(ret = ft_strjoin(s1, s2)))
		return (NULL);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (ret);
}
