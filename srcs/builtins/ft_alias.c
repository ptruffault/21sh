/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:43:00 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 12:43:02 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

void	ft_alias(t_shell *sh, char **argv)
{
	if (argv[1] == NULL)
		ft_puttenvv(sh->alias);
	else
		sh->alias = ft_setenv(sh->alias, &argv[1]);
}