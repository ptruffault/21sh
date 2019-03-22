
#include <shell42.h>


static t_process	*ft_get_process(t_process *p, unsigned int status)
{
	//t_process *tmp;

	while (p)
	{
		if (p->status == status && p->pid > 0)
			return (p);
		/*if (p->grp)
		{
			tmp = p->grp;
			while (tmp)
			{
				if (tmp->status == status && p->pid > 0)
					return (tmp);
				tmp = tmp->grp;
			}
		}*/
		p = p->next;
	}
	return (NULL);
}



void update_process_status(t_process *p, unsigned int to)
{
	char *stats[6];

	ft_process_tab_status(stats);
	while (p)
	{
		p->status = to;
		ft_printf("\t{%i} %s %s\n", p->pid, stats[p->status], p->cmd);
		p = p->grp;
	}
}


//kill tout les process de p->status == status } avec sig , le status des process es changer 
// sig == -1 -> put in bg avec iotcl

void ft_process_background(t_process *p)
{
	if ((ioctl(0, TIOCSPGRP, &p->pid)) != 0)
	{
		error("can't set this process in background", p->cmd);
		killpg(p->pid, SIGTSTP);
		update_process_status(p, SUSPENDED);
	}
	else
		update_process_status(p, RUNNING_BG);
}


int			kill_process(t_process *p, int sig, unsigned int status)
{
	t_process *tmp;
	int i;

	i = 0;
	while (p && (tmp = ft_get_process(p, status)))
	{
		i++;
		if (sig == -1)
			ft_process_background(tmp);
		else
		{
			if (sig == SIGINT || sig == SIGKILL)
				update_process_status(tmp, KILLED);
			else if (sig == SIGTSTP)
				update_process_status(tmp, SUSPENDED);
			else if (sig == SIGCONT)
				update_process_status(tmp, RUNNING_FG);
			killpg(tmp->pid, sig);
		}
	}
	return (i);
}
