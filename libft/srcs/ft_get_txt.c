/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:16:51 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 17:24:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_get_txt(int fd)
{
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	if (fd < 0)
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *))))
		return (NULL);
	tmp = NULL;
	while (get_next_line(fd, &tmp) && tmp && !ft_isempty(tmp))
	{
		ret = ft_realloc(ret, (i + 1) * sizeof(char *), (i + 2) * sizeof(char *));
		ret[i++] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ret[i] = NULL;
	return (ret);
}
