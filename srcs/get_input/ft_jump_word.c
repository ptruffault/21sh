/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 12:06:10 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/01 17:54:24 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	ft_jp_word_right(t_edit *e)
{
	int	x;

	x = e->curr;
	while (e->input[x] && ft_isspace(e->input[x]) == 1)
		x++;
	while (e->input[x] && ft_isspace(e->input[x]) == 0)
		x++;
	e->curr = x;
}

void	ft_jp_word_left(t_edit *e)
{
	int	x;

	x = e->curr;
	while (x > 0 && ft_isspace(e->input[x]) == 1)
		x--;
	while (x > 0 && ft_isspace(e->input[x]) == 0)
		x--;
	e->curr = x;
}
