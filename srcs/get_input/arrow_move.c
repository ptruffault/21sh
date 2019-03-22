/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:52:40 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

void	curr_move_right(t_edit *e)
{
	if ((size_t)e->curr < ft_strlen(e->hist->s))
		e->curr++;
}

void	curr_move_left(t_edit *e)
{
	if (e->curr > 0)
		e->curr--;
}

void	curr_go_last(t_edit *e)
{
	e->curr = ft_strlen(e->hist->s);
}

void	ft_home_key(t_edit *e)
{
	e->curr = 0;
}
