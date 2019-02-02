/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:04:08 by ptruffau          #+#    #+#             */
/*   Updated: 2018/08/20 15:04:10 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void ft_exit(void)
{
	t_tree *t;
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	t = ft_get_set_tree(NULL);
	ft_set_old_term(sh);
	ft_free_tshell(sh);
	ft_free_tree(t);
	ft_putendl("\033[00;31m21sh get killed\033[00m");
	exit(0);
}
