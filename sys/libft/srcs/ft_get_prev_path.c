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
	char *new;
	char *ptr;

	if (ft_strchr(path, '/') != NULL)
	{
		if (!(new = ft_strdup(path)))
			return (NULL);
		ptr = ft_strchr(new, '/');
		*ptr = '\0';
	}
	else if (!(new = ft_strdup(".\0")))
		return (NULL);
	return (new);
}
