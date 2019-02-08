/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:42:19 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 12:42:21 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

static void	init_jobs_tab(char *stat[5])
{
	stat[0] = "running foreground";
	stat[1] = "running background";
	stat[2] = "done";
	stat[3] = "suspended";
	stat[4] = "killed";
}

void		ft_jobs(t_shell *sh)
{
	t_process	*tmp;
	char		*stat[5];
	int			i;

	i = 0;
	tmp = sh->process;
	while (tmp)
	{
		ft_printf("[%i] %s -> %3i\t%s {%i}\n",
		i++, stat[tmp->status], tmp->ret, tmp->cmd, tmp->pid);
		tmp = tmp->next;
	}
}
