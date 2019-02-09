/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:28:15 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/05 13:27:36 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_open(char *path)
{
	int fd;

	if ((fd = open(path, O_CREAT | S_IRWXU, O_RDWR)) <= 2)
	{
		warning("can't acess", path);
		perror(NULL);
	}
	return (fd);
}
