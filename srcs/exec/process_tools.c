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

void ft_update_process_status(t_process *p, int pid, enum e_pstatus new_stat)
{
	while (p)
	{
		if (p->pid == pid)
		{
			p->status = new_stat;
			break;
		}
		p = p->next;
	}
}
