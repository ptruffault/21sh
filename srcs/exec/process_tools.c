/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:07:56 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:07:57 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

t_process	*ft_get_process(t_process *s, int pid)
{
	t_process *ret;

	ret = s;
	while (ret && ret->pid != pid)
		ret = ret->next;
	return (ret);
}

t_process	*ft_get_running_process(t_process *p)
{
	while (p)
	{
		if (p->status == RUNNING_FG)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int			kill_running_fg_process(t_process *p, int sig)
{
	t_process *tmp;

	if ((tmp = ft_get_running_process(p)))
	{
		if (sig == SIGINT)
			p->status = KILLED;
		if (sig == SIGTSTP)
			p->status = SUSPENDED;
		kill(p->pid, sig);
		return (1);
	}
	return (0);
}
