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

t_process *ft_wait_background(t_process *p)
{
	t_process *tmp;

	tmp = p;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG && waitpid(tmp->pid, &tmp->ret, WNOHANG) != -1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}


void sig_handler(int sig)
{
	t_shell *sh;
	t_process *tmp;
	int pid;

	ft_printf("SIG HANDLER %i\n", sig);
	pid = 0;
	sh = ft_get_set_shell(NULL);
	if (sig == SIGINT && sh && sh->process && !kill_running_fg_process(sh->process, SIGINT))
	{
		//^C in edition
	}
/*	if (sig == SIGTSTP && sh && sh->process)
		kill_running_fg_process(sh->process, SIGTSTP);*/

	//recupere un process finis en background 
	if (sig == SIGCHLD && sh && sh->process && (tmp = ft_wait_background(sh->process)))
		tmp->status = DONE;
}

void	set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
}

