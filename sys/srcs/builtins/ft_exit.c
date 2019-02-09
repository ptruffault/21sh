/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 13:09:40 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

void	ft_exit(void)
{
	t_tree	*t;
	t_shell	*sh;

	sh = ft_get_set_shell(NULL);
	t = ft_get_set_tree(NULL);
	ft_set_old_term(sh);
	ft_free_tshell(sh);
	ft_free_tree(t);
	ft_putendl_fd("\033[00;31m21sh get killed\033[00m", 2);
	exit(0);
}
