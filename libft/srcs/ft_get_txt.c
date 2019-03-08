/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:16:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 13:36:38 by adi-rosa         ###   ########.fr       */
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
		ret = ft_realloc(ret, (i + 1) * sizeof(char *),
		(i + 2) * sizeof(char *));
		if (!tmp)
			ret[i++] = ft_strdup(" ");
		else
			ret[i++] = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (i == 0)
		free(ret);
	ret[i] = NULL;
	return (ret);
}
