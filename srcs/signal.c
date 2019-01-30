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

void kill_running_fg_process(t_process *p)
{
	while(p)
	{
		if (p->status == RUNNING_FG)
		{
			kill(p->pid, 3);
			break;
		}
		p = p->next;
	}
}

void sig_handler(int sig)
{
	t_shell *sh;
	int pid;

	ft_printf("SIG HANDLER %i\n", sig);

	sh = ft_get_set_shell(NULL);
	if (sig == 2 && sh && sh->process)
		kill_running_fg_process(sh->process);
	if (sig == SIGCHLD && sh && sh->process)
	{
		pid = waitpid(-1, 0, 0);
		ft_update_process_status(sh->process, pid, DONE);
	}
}

void	set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGTTIN, sig_handler);
	signal(SIGTTOU, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
}

