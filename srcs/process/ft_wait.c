/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:44:39 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/22 17:56:54 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static const	t_sig_msg	g_signal_msg[] = {
	{.sig = SIGHUP, .rtn = 129, .msg = "Hangup"},
	{.sig = SIGINT, .rtn = 1, .msg = "SIGINT"},
	{.sig = SIGQUIT, .rtn = 131, .msg = "Quit"},
	{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction"},
	{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap"},
	{.sig = SIGABRT, .rtn = 134, .msg = "Abort"},
	//{.sig = SIGEMT, .rtn = 135, .msg = "emulate instruction executed"},
	{.sig = SIGFPE, .rtn = 136, .msg = "Floating exception"},
	{.sig = SIGKILL, .rtn = 137, .msg = "Killed"},
	{.sig = SIGBUS, .rtn = 138, .msg = "Bus error"},
	{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault"},
	{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call"},
	{.sig = SIGPIPE, .rtn = 141, .msg = "write one pipe with no one to read it"},
	{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock"},
	{.sig = SIGTERM, .rtn = 143, .msg = "Terminated"},
	{.sig = SIGURG, .rtn = 0, .msg = ""},
	{.sig = SIGSTOP, .rtn = 0, .msg = "Suspended"},
	{.sig = SIGTSTP, .rtn = 0, .msg = "Suspended"},
	{.sig = SIGCONT, .rtn = 0, .msg = "Continued"},
	{.sig = SIGCHLD, .rtn = 0, .msg = "Done"},
	{.sig = SIGTTIN, .rtn = 0,
		.msg = "background read attempted from control terminal"},
	{.sig = SIGTTOU, .rtn = 0,
		.msg = "background write attempted from control terminal"},
	{.sig = SIGIO, .rtn = 0, .msg = "I/O is possible on a descriptor"},
	{.sig = SIGXCPU, .rtn = 152, .msg = "Cputime limit exceeded"},
	{.sig = SIGXFSZ, .rtn = 153, .msg = "Filesize limit exceeded"},
	{.sig = SIGVTALRM, .rtn = 142, .msg = "Alarm clock"},
	{.sig = SIGPROF, .rtn = 155, .msg = "Profiling time alarm"},
	{.sig = SIGUSR1, .rtn = 158, .msg = "User signal 1"},
	{.sig = SIGUSR2, .rtn = 159, .msg = "User signal 2"},
	{.msg = NULL}
};

int	ft_signal_check(t_process *p)
{
	int i;

	i = 0;
	if (p->sig <= 0)
		return (0);
	while (g_signal_msg[i].msg != NULL)
	{
		if (g_signal_msg[i].sig == p->sig)
		{
			ft_putstr(g_signal_msg[i].msg);
			return (1);
		}
		i++;
	}
	return (0);
}

void		ft_wait(t_process *p)
{
	while (p)
	{
		if ((p->builtins == TRUE && p->status == RUNNING_FG)
			|| (p->status == RUNNING_FG
			&& waitpid(p->pid, &p->ret, 0) > 0))
		{
			if (p->builtins == FALSE && (WIFSIGNALED(p->ret) || p->sig > 0))
			{
				p->status = KILLED;
				p->sig = (p->sig > 0 ? p->sig : WTERMSIG(p->ret));
				p->ret = p->sig + 128;
				ft_put_process(p);
			}
			else if (WIFEXITED(p->ret))
				p->ret = WEXITSTATUS(p->ret);
			if (p->status != KILLED)
				p->status = DONE;
		}
		p = p->grp;
	}
}
