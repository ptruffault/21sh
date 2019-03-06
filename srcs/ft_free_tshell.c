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
	ft_free_tenvv(sh->env);
	ft_free_tenvv(sh->intern);
	ft_free_tenvv(sh->alias);
	ft_free_tprocess(sh->process);
	ft_free_thist(sh->hist);
	ft_strdel(&sh->clipboard);
	free(sh->saved_term);
}
