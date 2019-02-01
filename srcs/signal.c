/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/03 12:57:51 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

t_tree		*ft_get_set_tree(t_tree *new_t)
{
	static t_tree	*stored_t = NULL;

	if (new_t)
		stored_t = new_t;
	return (stored_t);
}

void abort_exit(int s)
{
	(void)s;
	ft_free_tenvv(ft_get_set_envv(NULL));
	ft_free_tree(ft_get_set_tree(NULL));
	error("21sh aborted", NULL);
	exit(0);

}

int kill_running_fg_process(const t_process *src, int sig)
{
	t_process *p;

	p = (t_process *)src;
	while(p)
	{
		if (p->status == RUNNING_FG)
		{
			printf("killing %i \n",p->pid );
			kill(p->pid, sig);
			p->status = KILLED;
			p->ret = sig;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

void sig_handler(int sig)
{
	t_shell *sh;
	t_process *tmp;
	int pid;
	int status;

	ft_printf("SIG HANDLER %i\n", sig);
	pid = 0;
	sh = ft_get_set_shell(NULL);
	if (sig == SIGINT && sh && sh->process && !kill_running_fg_process(sh->process, SIGINT))
		ft_putchar('\n');
	if (sig == SIGCHLD && sh && sh->process)
	{
		if ((pid = waitpid(-1, &status,0)) != -1 
		&& (tmp = ft_get_process(sh->process, pid))
		&& tmp->status == RUNNING_BG)
		{
			tmp->status = DONE;
			tmp->ret = status;
		}
	}
}

void	set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
}

