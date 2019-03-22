/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:32:37 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 15:09:42 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, int prev_size, int new_size)
{
	void	*new;

	if (!ptr || prev_size < 0 || new_size < 0)
		return (NULL);
	if (!(new = ft_memalloc(new_size)))
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new, ptr, prev_size < new_size ? prev_size : new_size);
	ft_memdel(&ptr);
	return (new);
}
