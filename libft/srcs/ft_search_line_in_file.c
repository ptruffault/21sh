/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:28:44 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:32:52 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_search_line_in_file(char *path, char *src)
{
	int		fd;
	int		i;
	char	**arr;
	char	*ret;
	char	*tmp;

	if ((fd = ft_open(path)) <= 2)
		return (NULL);
	arr = ft_get_txt(fd);
	tmp = ft_stradd_char(ft_strdup(src), '*');
	i = -1;
	while (arr[++i])
	{
		if (ft_match(arr[i], tmp) && !ft_strequ(src, arr[i]))
		{
			ret = ft_strdup(arr[i]);
			ft_strdel(&tmp);
			ft_freestrarr(arr);
			close(fd);
			return (ret);
		}
	}
	ft_freestrarr(arr);
	ft_strdel(&tmp);
	return (NULL);
}
