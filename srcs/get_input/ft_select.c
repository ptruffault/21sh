/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:56:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/01 17:54:56 by adi-rosa         ###   ########.fr       */
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
