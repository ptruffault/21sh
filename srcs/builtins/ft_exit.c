/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:09:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int		ft_quit(int exit_code, t_shell *sh)
{
	ft_free_tshell(sh);
	return (exit_code);
}

void	ft_exit(char *nbr, t_shell *sh)
{
	int		exit_code;

	if (nbr)
		exit_code = ft_atoi(nbr);
	else
		exit_code = 0;
	exit(ft_quit(exit_code, sh));
}
