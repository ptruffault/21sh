/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prev_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:16:51 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 17:24:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_get_prev_path(char *path)
{
	char	*new;
	int		len;
	int		i;

	new = NULL;
	if (ft_strchr(path, '/'))
	{
		len = ft_strlen(path);
		i = len - 1;
		while (path[i] != '/')
		{
			i--;
		}
		new = ft_strndup(path, i);
	}
	return (new);
}
