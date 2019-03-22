/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:37 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/22 15:30:45 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int				ft_isparenth(char c)
{
	if (c == '{' || c == '(')
		return (1);
	else if (c == '}' || c == ')')
		return (2);
	return (0);
}

t_hist			*new_hist(void)
{
	t_hist	*n;

	if (!(n = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	n->s = NULL;
	n->next = NULL;
	n->prev = NULL;
	return (n);
}

t_hist			*init_hist(char *hist)
{
	t_hist	*ret;
	t_hist	*tmp;
	int		fd;
	char	*line;

	ret = NULL;
	tmp = NULL;
	if ((fd = ft_open(hist, O_RDWR | O_CREAT | O_NOFOLLOW, 511)) >= 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (!(tmp = new_hist()))
				return (ft_free_thist(ret));
			if (line)
				tmp->s = line;
			else if (!(tmp->s = ft_strnew(0)))
				return (ft_free_thist(ret));
			tmp->next = !ret ? NULL : ret;
			if (tmp->next)
				tmp->next->prev = tmp;
			ret = tmp;
		}
		ft_close(fd);
	}
	return (tmp);
}
