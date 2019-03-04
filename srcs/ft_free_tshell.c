/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:26:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 15:26:13 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell42.h"

void	ft_free_tshell(t_shell *sh)
{
	if (sh->env)
		ft_free_tenvv(sh->env);
	if (sh->intern)
		ft_free_tenvv(sh->intern);
	if (sh->alias)
		ft_free_tenvv(sh->alias);
	if (sh->process)
		ft_free_tprocess(sh->process);
	if (sh->hist)
		ft_free_thist(sh->hist);
	ft_strdel(&sh->clipboard);
	if (sh->saved_term)
		free(sh->saved_term);
}
