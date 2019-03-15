/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:16:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 17:43:24 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_get_txt(int fd)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	if (fd < 0 || !(ret = (char **)malloc(sizeof(char *))))
		return (NULL);
	tmp = NULL;
	while (get_next_line(fd, &tmp))
	{
		ret = ft_realloc(ret, (size_t)(i + 1) * sizeof(char *),
		(size_t)(i + 2) * sizeof(char *));
		if (!tmp)
			ret[i++] = ft_strdup(" ");
		else
			ret[i++] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ret[i] = tmp;
	if (i == 0)
	{
		ft_strdel(&ret[i]);
		free(ret);
		return (NULL);
	}
	return (ret);
}
