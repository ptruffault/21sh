/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:43:08 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/21 14:33:49 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char		*ft_strsub_gnl(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = NULL;
	if (s == NULL)
		return (0);
	if (!(res = ft_strnew(len)))
		return (NULL);
	while (i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

static char		*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new;
	size_t	ls1;
	size_t	ls2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (!(new = ft_strnew(ls1 + ls2)))
		return (NULL);
	new = ft_strcpy(new, s1);
	new = ft_strcat(new, s2);
	return (new);
}

static	int		ft_check_charriot(char *buff, char **res)
{
	char	*tmp;
	char	*tofree;
	char	*s;

	tofree = *res;
	s = buff;
	if ((tmp = ft_strchr(buff, '\n')) != NULL)
		s = ft_strsub_gnl(buff, 0, tmp - buff);
	if (!(*res = ft_strjoin_gnl(*res, s)))
	{
		ft_strdel(&tofree);
		if (tmp != NULL)
			ft_strdel(&s);
		return (-1);
	}
	ft_strdel(&tofree);
	if (tmp != NULL)
	{
		ft_strdel(&s);
		ft_strcpy(buff, tmp + 1);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		buff[BUFF_SIZE + 1];
	int				i;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	if (ft_strlen(buff) > 0)
		if (ft_check_charriot(buff, line) == 1)
			return (1);
	while ((i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (ft_check_charriot(buff, line) == 1)
			return (1);
	}
	if (ft_strlen(buff) == 0)
	{
		ft_strdel(line);
		return (i);
	}
	ft_memset(buff, 0, 1);
	return (1);
}
