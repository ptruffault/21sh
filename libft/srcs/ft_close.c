/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:03:55 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:04:50 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_close(int fd)
{
	char *n;

	if (fd >= 0 && close(fd) == -1)
	{
		n = ft_itoa(fd);
		warning("close failure fd ->", n);
		perror(NULL);
		ft_strdel(&n);
		return (0);
	}
	return (1);
}
