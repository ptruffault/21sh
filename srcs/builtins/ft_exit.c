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


void free_tshell(void)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	ft_free_tenvv(sh->env);
	ft_free_tenvv(sh->intern);
	ft_free_tenvv(sh->alias);
	ft_free_tprocess(sh->process);
	if ((tcsetattr(0, TCSADRAIN, &sh->saved_term)) == -1)
		warning("Error while set attr of term, not termcaps", NULL);
}

void ft_exit(t_tree *t, t_envv *e)
{
	ft_free_tree(t);
	ft_free_tenvv(e);
	ft_putendl("\033[00;31m21sh get killed\033[00m");
	exit(0);
}
