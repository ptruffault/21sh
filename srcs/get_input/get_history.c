/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:37 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/01 17:51:58 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int		ft_isparenth(char c)
{
	if (c == '{' || c == '(')
		return (1);
	else if (c == '}' || c == ')')
		return (2);
	return (0);
}

t_hist	*new_hist(void)
{
	t_hist	*n;

	if (!(n = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	n->s = NULL;
	n->next = NULL;
	return (n);
}

t_hist	*add_hist(t_hist *head, char *s)
{
	t_hist	*new;

	if (!(new = new_hist()))
		return (NULL);
	new->s = ft_strdup(s);
	new->next = head;
	return (new);
}

t_hist	*ft_read_hist(int i, char **arr)
{
	t_hist *new;
	t_hist *tmp;

	new = new_hist();
	tmp = new;
	while (i >= 0)
	{
		tmp->s = ft_strdup(arr[i--]);
		tmp->next = new_hist();
		tmp = tmp->next;
	}
	return (new);
}

t_hist	*init_hist(char *hist)
{
	t_hist	*new;
	int		fd;
	char	**arr;
	int		i;

	new = NULL;
	if ((fd = open(hist, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) >= 0)
	{
		if ((arr = ft_get_txt(fd)))
		{
			if ((i = ft_strarrlen(arr) - 1) > 0)
				new = ft_read_hist(i, arr);
			ft_freestrarr(arr);
		}
		ft_close(fd);
	}
	else
		perror(hist);
	return (new);
}
