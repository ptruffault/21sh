/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:40:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/21 16:26:38 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	ft_jump_line_up(t_edit *e)
{
	if (e->curr >= e->width)
		e->curr -= e->width;
}

void	ft_select_line_up(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	ft_jump_line_up(e);
}

void	ft_jump_line_down(t_edit *e)
{
	if (ft_strlen(e->hist->s) - e->curr >= e->width)
		e->curr += e->width;
}

void	ft_select_line_down(t_edit *e)
{
	if (e->select == -1)
	{
		e->select = 1;
		e->select_pos = e->curr;
	}
	ft_jump_line_down(e);
}
