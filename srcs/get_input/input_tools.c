/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:21:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/01 18:00:37 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_add_char(char buf, t_edit *e)
{
	int i;
	int size;

	if (e->select != -1)
		e->select = -1;
	if (!ft_isprint(buf))
		return ;
	i = ft_strlen(e->input);
	size = ft_strlen(e->input) + 1;
	while (i > 1 && i > e->curr)
	{
		e->input[i] = e->input[i - 1];
		i--;
	}
	e->input[e->curr] = buf;
	e->input = ft_realloc(e->input, size, size + 1);
	e->input[size] = '\0';
	e->curr++;
}

void	delete_left(t_edit *e)
{
	int		i;
	int		j;
	char	*tmp;

	if (e->curr < 1)
		return ;
	i = 0;
	j = 0;
	tmp = ft_strnew(ft_strlen(e->input));
	while (e->input[j])
	{
		if (j != e->curr - 1)
			tmp[i++] = e->input[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->input);
	e->input = tmp;
	curr_move_left(e);
}

void	delete_on(t_edit *e)
{
	int		i;
	int		j;
	char	*tmp;

	if ((size_t)e->curr == (size_t)ft_strlen(e->input))
		return ;
	i = 0;
	j = 0;
	tmp = ft_strnew(ft_strlen(e->input));
	while (e->input[j])
	{
		if (j != e->curr)
			tmp[i++] = e->input[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->input);
	e->input = tmp;
}
