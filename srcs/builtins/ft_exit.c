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

void	ft_exit(char *nbr, t_shell *sh)
{
	int		exit_code;

	if (nbr)
		exit_code = ft_atoi(nbr);
	else
		exit_code = 0;
	kill_process(sh->process, SIGINT, RUNNING_FG);
	kill_process(sh->process, SIGINT, RUNNING_BG);
	kill_process(sh->process, SIGINT, SUSPENDED);
	if (sh->interactive == TRUE)
		ft_set_old_term(sh, 0);
	else
		ft_strdel(&sh->txt);
	ft_free_tshell(sh);
	exit(exit_code);
}
