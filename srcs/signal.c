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

void		ft_sigint(t_shell *sh)
{
	unsigned long key;

	key = KEY_ENTER;
	if (!(sh && sh->process
	&& kill_running_fg_process(sh->process, SIGINT)))
	{
		if (isatty(0) && sh->e.input)
		{
			ft_strdel(&sh->e.input);
			sh->e = init_tedit(sh);
		}
		if (sh->heredoc != 0)
		{
			sh->heredoc = -1;
			sh->e.edited = TRUE;
			write(8, &key, 0);
		}
		ft_disp(sh);
	}
}

void		sig_handler(int sig)
{
	t_shell		*sh;
	t_process	*tmp;

	sh = ft_get_set_shell(NULL);
	if (sig == SIGINT)
		ft_sigint(sh);
	if (sig == SIGWINCH)
		ft_update_windows(&sh->e);
	if (sig == SIGTSTP && sh->process)
		kill_running_fg_process(sh->process, SIGTSTP);
	if (sig == SIGCHLD && sh->process
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
