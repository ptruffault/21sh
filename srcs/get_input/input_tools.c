/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:21:10 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/13 13:21:12 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_add_char(char buf, t_edit *e)
{
	int i;

	if (!ft_isprint(buf))
		return ;
	i = e->size - 1;
	while (i > 1 && i > e->curr)
	{
		e->input[i] = e->input[i - 1];
		i--;
	}
	e->input[e->curr++] = buf;
	e->input = ft_realloc(e->input, e->size , e->size + 1);
	e->input[e->size++] = '\0';
	curs_move_right(e);
	ft_print_line(e);
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
	tmp = ft_strnew(--e->size);
	while (e->input[j])
	{
		if (j != e->curr - 1)
			tmp[i++] = e->input[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->input);
	e->input = tmp;
	e->curr--;
	curs_move_left(e);
	ft_print_line(e);
}

void	delete_on(t_edit *e)
{
	int		i;
	int		j;
	char	*tmp;

	if (e->curr == e->size)
		return ;
	i = 0;
	j = 0;
	tmp = ft_strnew(--e->size);
	while (e->input[j])
	{
		if (j != e->curr)
			tmp[i++] = e->input[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->input);
	e->input = tmp;
	ft_print_line(e);
}