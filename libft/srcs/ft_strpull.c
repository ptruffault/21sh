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
	if (src - ptr == 0)
		return (ft_strjoin(value, src + len + 1));
	else if (src - ptr > 0)
		return (ft_strjoin_fr(ft_strndup(src, src - ptr), 
	ft_strjoin(value, ptr + len)));
	return (NULL);
}
