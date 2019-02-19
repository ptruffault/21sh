/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:36:07 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 15:52:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncut(char *str, int f)
{
	int i;

	i = 0;
	while (str[i] != '\0' && i < f)
	{
		i++;
		str++;
	}
	return (str);
}