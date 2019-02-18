/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:19:08 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 16:22:38 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_file	*test_upper(t_file *file, int (*f)(t_file *file, t_file *tmp))
{
	t_file *tmp;

	tmp = file->next;
	while (tmp)
	{
		if ((*f)(file, tmp) == 1)
			return (tmp);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

static int		ft_sort_parcours(t_file *prev, int (*f)(t_file *fe, t_file *t))
{
	int		ret;
	t_file	*file;
	t_file	*tmp;

	file = prev->next;
	ret = 1;
	while (file->next)
	{
		if ((tmp = test_upper(file, f)))
		{
			ret = 0;
			prev->next = file->next;
			file->next = tmp->next;
			tmp->next = file;
			file = prev->next;
		}
		prev = prev->next;
		file = file->next;
	}
	return (ret);
}

t_file			*ft_sort_tfile(t_file *file, int (*f)(t_file *fi, t_file *t))
{
	t_file	*prev;
	int		is_sort;

	if (!(*f) || !(file))
		return (NULL);
	if (!(file->next))
		return (file);
	is_sort = 0;
	prev = ft_new_tfile();
	prev->next = file;
	while (is_sort == 0)
		is_sort = ft_sort_parcours(prev, f);
	file = prev->next;
	free(prev);
	return (file);
}
