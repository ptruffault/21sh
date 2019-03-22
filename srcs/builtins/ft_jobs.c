/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:42:19 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void ft_job_prompt(t_process *tmp, char *stat[6], int id)
{
	t_process *grp;

	ft_printf("ID % -5i%-25s%i %-20s%i\033[00m\n",
	id, stat[tmp->status], tmp->ret, tmp->cmd, tmp->pid);
	if (tmp->grp)
	{
		grp = tmp->grp;
		while (grp)
		{
			if (grp->cmd)
				ft_printf(" |       %-25s%i %-20s%i\033[00m\n",
				stat[grp->status], grp->ret, grp->cmd, grp->pid);
			grp = grp->grp;
		}
	}
}

int		ft_hi(t_shell *sh)
{
	t_process	*tmp;
	char 		*stat[6];
	int			id;

	id = 0;
	tmp = sh->process;
	ft_process_tab_status(stat);
	while (tmp)
	{
		if (tmp->cmd)
			ft_job_prompt(tmp, stat, id++);
		tmp = tmp->next;
	}
	return (0);
}

int 	ft_jobs(t_shell *sh)
{
	t_process	*tmp;
	char 		*stat[6];
	int			id;

	id = 0;
	 ft_process_tab_status(stat);
	tmp = sh->process;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG || tmp->status == SUSPENDED)
			ft_job_prompt(tmp, stat, id++);
		tmp = tmp->next;
	}
	return (0);
}
