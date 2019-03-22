/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>
#include "../includes/get_input.h"


/*static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .rtn = 129, .msg = "Hangup"},
		{.sig = SIGINT, .rtn = 1, .msg = ""},
		{.sig = SIGQUIT, .rtn = 131, .msg = "Quit"},
		{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction"},
		{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap"},
		{.sig = SIGABRT, .rtn = 134, .msg = "Abort"},
		{.sig = SIGFPE, .rtn = 136, .msg = "Floating exception"},
		{.sig = SIGKILL, .rtn = 137, .msg = "Killed"},
		{.sig = SIGBUS, .rtn = 138, .msg = "Bus error"},
		{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault"},
		{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call"},
		{.sig = SIGPIPE, .rtn = 141, .msg = "Broken pipe"},
		{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGTERM, .rtn = 143, .msg = "Terminated"},
		{.sig = SIGURG, .rtn = 0, .msg = ""},
		{.sig = SIGXCPU, .rtn = 152, .msg = "Cputime limit exceeded"},
		{.sig = SIGXFSZ, .rtn = 153, .msg = "Filesize limit exceeded"},
		{.sig = SIGVTALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGPROF, .rtn = 155, .msg = "Profiling time alarm"},
		{.sig = SIGUSR1, .rtn = 158, .msg = "User signal 1"},
		{.sig = SIGUSR2, .rtn = 159, .msg = "User signal 2"},
		{.msg = NULL}
};
*/

void		sig_handler(int sig)
{
	t_shell		*sh;

	if ((sh = ft_get_set_shell(NULL)))
	{
		if (sig == SIGINT)
		{
			if (sh->interactive == TRUE && !kill_process(sh->process, SIGINT, RUNNING_FG))
				ft_disp(sh);
			else if (sh->interactive == FALSE)
				ft_exit("2", sh);
		}
		else if (sig == SIGWINCH && sh)
			ft_update_windows(&sh->e);
		else if (sig == SIGTSTP && sh && sh->process)
			kill_process(sh->process, SIGTSTP, RUNNING_FG);
		else if (sig == SIGCHLD && sh && sh->process)
			ft_wait_background(sh);
	}
}

void		set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGCHLD, sig_handler);
	signal(SIGWINCH, sig_handler);
}
