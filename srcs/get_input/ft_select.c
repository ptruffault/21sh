/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:56:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	ft_select_right(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	if (e->curr + 1 < ft_strlen(e->hist->s))
		e->curr++;
}

void	ft_select_left(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	if (e->curr > 0)
		e->curr--;
}

void	ft_select_end(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	curr_go_last(e);
}

void	ft_select_home(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	ft_home_key(e);
}
