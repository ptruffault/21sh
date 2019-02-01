/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void ft_add_process(t_shell *sh, t_process *new)
{
	if (new)
	{
		new->next = sh->process;
		sh->process = new;
	}
}

t_process *ft_get_process(t_process *s, int pid)
{
	t_process *ret;

	ret = s;
	while (ret && ret->pid != pid)
		ret = ret->next;
	return (ret);
}


int kill_running_fg_process(t_process *p, int sig)
{
	while(p)
	{
		if (p->status == RUNNING_FG)
		{
			if (sig == SIGINT)
				p->status = KILLED;
			if (sig == SIGTSTP)
				p->status = SUSPENDED;
			kill(p->pid, sig);
			return (1);
		}
		p = p->next;
	}
	return (0);
}
