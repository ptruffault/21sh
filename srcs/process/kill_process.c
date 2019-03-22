
#include <shell42.h>


static t_process	*ft_get_process(t_process *p, unsigned int status)
{
	t_process *tmp;

	while (p)
	{
		if (p->status == status && p->pid > 0 && !ft_strequ(p->cmd, "exit"))
			return (p);
		if (p->grp)
		{
			tmp = p->grp;
			while (tmp)
			{
				if (tmp->status == status && p->pid > 0 && !ft_strequ(tmp->cmd, "exit"))
					return (tmp);
				tmp = tmp->grp;
			}
		}
		p = p->next;
	}
	return (NULL);
}

int			kill_process(t_process *p, int sig, unsigned int status)
{
	t_process *tmp;
	int i;

	i = 0;
	while (p && (tmp = ft_get_process(p, status)))
	{
		i++;
		if (sig == SIGINT || sig == SIGKILL)
			tmp->status = KILLED;
		ft_printf("signal %i send to %s\n", sig, tmp->cmd);
		kill(tmp->pid, sig);
	}
	return (i);
}
