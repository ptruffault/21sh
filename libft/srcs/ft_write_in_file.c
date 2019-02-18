/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_in_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:27:04 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:53:52 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_write_in_file(char *path, char *str)
{
	int fd;

	if ((fd = open(path, O_RDWR | O_CREAT | O_APPEND
					, S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		return ;
	ft_putendl_fd(str, fd);
	ft_close(fd);
}
