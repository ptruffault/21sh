/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_from_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:18:28 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 16:18:30 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_strdel_from_arr(int n, void *arr, size_t width, int len)
{
	char			*to_remove;

	to_remove = (((char*)arr) + n * width);
	ft_memmove((void*)to_remove, (void*)(to_remove + width)
				, (len - n - 1) * width);
}
