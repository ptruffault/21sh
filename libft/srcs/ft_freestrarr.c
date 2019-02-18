/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:57:04 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 11:11:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_freestrarr(char **arr)
{
	int i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i] != NULL)
		ft_strdel(&arr[i++]);
	free(arr);
}
