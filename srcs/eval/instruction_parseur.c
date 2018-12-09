/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instrcution_parseur.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:22:05 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:22:06 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char **ft_get_file_content(char *path)
{
	int fd;
	char **ret;

	ret = NULL;
	if (!path)
	{
		warning ("file or needed as argument", "< [file] ");
		return (NULL);
	}
	if ((fd = ft_open(path)) > 0)
	{
		ret = ft_get_txt(fd);
		close(fd);
	}
	return (ret);
}


