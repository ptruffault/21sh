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

#include "../../includes/shell42.h"


void	ft_delete_process(int pid)
{
	t_shell *sh;
	t_process *p;
	t_process *tmp;

	sh = ft_get_set_shell(NULL);
	if ((p = sh->process))
	{
		if (p->pid == pid)
		{
			sh->process = p->next;
			p->next = NULL;
			ft_reset_fd(p->fd);
			ft_free_tprocess(p);
		}
	}
	else
	{
		while (p && p->next)
		{
			if (p->next->pid == pid)
			{
				tmp = p->next;
				p->next = tmp->next;
				tmp->next = NULL;
				ft_free_tprocess(tmp);
			}
			p = p->next;
		}
	}
}


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

void		ft_init_fd(int fd[3])
{
	fd[0] = 0;
	fd[1] = 1;
	fd[2] = 2;
}


t_process	*init_process(t_tree *t, t_shell *sh)
{
	t_process	*new;

	new = NULL;
	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		ft_init_fd(new->fd);
		if (t->o_type == O_BACK)
			new->status = RUNNING_BG;
		else
			new->status = RUNNING_FG;
		new->ret = -1;
		new->pid = 0;
		if (!(new->argv = ft_twordto_arr(t->cmd)))
		{
			free(new);
			return (NULL);
		}
		if (check_builtin(*new->argv) && (new->cmd = ft_strdup(*new->argv)))
			new->builtins = TRUE;
		else if ((new->cmd = get_bin_path(*new->argv, sh->env)))
			new->builtins = FALSE;
		else
		{
			ft_delete_process(new->pid);
			return (NULL);
		}
		new->next = sh->process;
		sh->process = new;
	}
	return (new);
}
