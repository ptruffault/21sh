/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:56:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/18 14:23:03 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_select_right(t_edit *e)
{
	if (e->select == -1)
		e->select = e->curr;
	if ((size_t)e->curr + 1 < ft_strlen(e->input))
		e->curr++;
}

void	ft_select_left(t_edit *e)
{
	if (e->select == -1)
		e->select = e->curr;
	if (e->curr > 0)
		e->curr--;
}

void	ft_select_end(t_edit *e)
{
	if (e->select == -1)
		e->select = e->curr;
	curr_go_last(e);
}

void	ft_select_home(t_edit *e)
{
	if (e->select == -1)
		e->select = e->curr;
	ft_home_key(e);
}
