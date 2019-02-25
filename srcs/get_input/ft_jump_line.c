/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 12:40:09 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/18 14:22:40 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_jump_line_up(t_edit *e)
{
	if (e->curr >= e->width)
		e->curr -= e->width;
}

void	ft_jump_line_down(t_edit *e)
{
	if (ft_strlen(e->input) - (size_t)e->curr >= (size_t)e->width)
		e->curr += e->width;
}
