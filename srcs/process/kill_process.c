/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:44:01 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/22 17:58:05 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void	ft_kill(t_process *p, int sig)
{
	if (p && p->status != DONE && p->status != KILLED
	&& 1 <= sig && sig <= 31)
	{
		p->sig = sig;
		if (p->builtins == FALSE && p->pid > 0)
			kill(p->pid, sig);
	}
}

static void	ft_killgrp(t_process *p, int sig)
{
	while (p)
	{
		ft_kill(p, sig);
		p = p->grp;
	}
}

int			kill_process(t_process *p, int sig, unsigned int status)
{
	int i;

	i = 0;
	while (p)
	{
		if (p->status == status)
		{
			ft_killgrp(p, sig);
			i++;
		}
		p = p->next;
	}
	return (i);
}
