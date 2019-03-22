/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 17:16:51 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 17:42:02 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_get_txt(int fd)
{
	char	**ret;
	char 	*tmp;
	int		gnl;
	int		i;

	i = 0;
	ret = NULL;
	if (fd >= 0 && (ret = (char **)malloc(sizeof(char *))))
	{
		while ((gnl = get_next_line(fd, &tmp)) == 1)
		{
			if (tmp && (!(ret = ft_realloc(ret, (i + 1) * sizeof(char *),
			(i + 2) * sizeof(char *)))
			|| !(ret[i++] = ft_strdup(tmp))))
				return (NULL);
			ret[i] = NULL;
			ft_strdel(&tmp);
		}
		get_next_line(-1, &tmp);
		if  (i == 0)
		{
			free(ret);
			return (NULL);
		}
		if (gnl == -1)
			ft_freestrarr(&ret);
	}
	return (ret);
}
