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

#include "../includes/shell42.h"
#include "../includes/get_input.h"

t_process	*ft_wait_background(t_process *p)
{
	t_process *tmp;

	tmp = p;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG
		&& waitpid(tmp->pid, &tmp->ret, WNOHANG) != -1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		sig_handler(int sig)
{
	t_shell		*sh;
	t_process	*tmp;

	sh = ft_get_set_shell(NULL);
	if (sig == SIGINT && !(sh && sh->process
	&& kill_running_fg_process(sh->process, SIGINT)))
		ft_disp(sh);
	if (sig == SIGWINCH && sh)
		ft_update_windows(&sh->e);
	if (sig == SIGTSTP && sh && sh->process)
		kill_running_fg_process(sh->process, SIGTSTP);
	if (sig == SIGCHLD && sh && sh->process
	&& (tmp = ft_wait_background(sh->process)))
	{
		ft_reset_fd(tmp);
		tmp->status = DONE;
	}
	if (sig == SIGKILL)
		ft_exit("9");
}

void		set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGKILL, sig_handler);
}
