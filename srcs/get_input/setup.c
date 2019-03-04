/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:23:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/05 12:29:43 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

t_edit	init_tedit(t_shell *sh)
{
	ft_update_windows(&sh->e);
	sh->e.edited = FALSE;
	sh->e.curr = 0;
	sh->e.pos = 0;
	sh->e.input = ft_strnew(1);
	sh->e.pos_hist = -1;
	sh->e.hist = sh->hist;
	sh->e.select = -1;
	return (sh->e);
}

void	free_tedit(t_edit *e)
{
	ft_strdel(&e->input);
	e = NULL;
}
