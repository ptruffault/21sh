/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:03:27 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:03:28 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char **ft_strarrdup(char **src)
{
	int i;
	char **new;

	i = -1;
	if (!(new = (char **)malloc(sizeof(char) * ft_strarrlen(src))))
		return (NULL);
	while (src[++i])
		new[i] = ft_strdup(src[i]);
	return (new);
}
