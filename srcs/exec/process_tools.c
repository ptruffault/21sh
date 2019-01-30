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

t_process *new_process(int pid, char *path, t_tree *t)
{
	t_process *new;

	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		new->pid = pid;
		new->cmd = ft_strdup(path);
		if (t->o_type == O_BACK)
			new->status = RUNNING_BG;
		else
			new->status = RUNNING_FG;
		new->fd[0]
		new->ret = -1;
		new->next = NULL;
	}
	return (new);
}

void ft_add_process(t_shell *sh, t_process *new)
{
	if (new)
	{
		new->next = sh->process;
		sh->process = new;
	}
}