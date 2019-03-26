#include <shell42.h>



static void 	ft_putpid_ret(t_process *p)
{
	t_shell *sh;

	if (p->builtins == FALSE)
		ft_printf("\x1B[00;31m{\x1B[00m%i\x1B[00;31m}\x1B[00m ", p->pid);
	else if ((sh = ft_get_set_shell(NULL)))
		ft_printf("\x1B[00;31m{\x1B[01;36m%i\x1B[00;31m}\x1B[00m ", sh->pid);

	if (p->status == DONE || p->status == SUSPENDED || p->status == KILLED)
	{
		if (p->ret == 0)
			ft_printf("\x1b[1;32;42m  0  \x1B[00m ", p->ret);
		else
			ft_printf("\x1b[1;34;41m%-4i \x1B[00m ", p->ret);
	}
	else
		ft_printf("      ");
}

void	ft_put_process(t_process *p)
{	
	char *stat[6];

	ft_process_tab_status(stat);
	ft_putpid_ret(p);
	ft_printf("%-25s", stat[p->status]);
	if (p->builtins == TRUE)
		ft_printf(" \x1B[1;36m%-17s\x1B[00;31m", p->cmd);
	else
		ft_printf(" %-17s\x1B[00;31m", p->cmd);
	ft_signal_check(p);
	ft_putstr("\x1B[00m\n");
}

void ft_job_prompt(t_process *tmp, int id)
{
	t_process *grp;

	if (id == -1)
		ft_printf("    ");
	else
	{
		if (id == 0)
			ft_printf("\x1B[04m ID  PID    RETURN   STATUS    PATH         \x1B[00m\n");
		ft_printf("-\x1B[01;34m%- 2i\x1B[00m", id);
	}
	ft_put_process(tmp);
	grp = tmp->grp;
	while (grp)
	{
		if (grp->cmd)
		{
			ft_printf("  \x1B[1;35m|\x1B[00m ");
			ft_put_process(grp);
		}
		grp = grp->grp;
	}
}

int		ft_hi(t_shell *sh)
{
	t_process	*tmp;
	int			id;
	char		*stdin;

	id = 0;
	if (!isatty(STDIN_FILENO))
	{
		ft_job_prompt(sh->process, -1);
		while (get_next_line(STDIN_FILENO, &stdin))
		{
			ft_putendl(stdin);
			ft_strdel(&stdin);
		}
		return (0);
	}
	tmp = sh->process;
	while (tmp)
	{
		if (tmp->cmd)
			ft_job_prompt(tmp, id++);
		tmp = tmp->next;
	}
	return (0);
}