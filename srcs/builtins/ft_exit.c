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

void	ft_kill_all_running_process(t_process *p, int sig)
{
	while (p)
	{
		if ((p->status == RUNNING_FG
		|| p->status == RUNNING_BG) && p->pid != 0)
			kill(p->pid, sig);
		p = p->next;
	}
}

void	ft_exit(char *nbr)
{
	t_shell	*sh;
	int		exit_code;

	if (nbr)
		exit_code = ft_atoi(nbr);
	else
		exit_code = 0;
	sh = ft_get_set_shell(NULL);
	ft_kill_all_running_process(sh->process, SIGKILL);
	ft_set_old_term(sh);
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	ft_putstr_fd("\033[00;31m21sh get killed\033[00m\n-> ", 2);
	ft_putnbr_fd(exit_code, 2);
	ft_putchar_fd('\n', 2);
	exit(exit_code);
}
