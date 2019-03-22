#include <shell42.h>

static const t_sig_msg	g_signal_msg[] = {
		{.sig = SIGHUP, .rtn = 129, .msg = "Hangup"},
		{.sig = SIGINT, .rtn = 1, .msg = "Interupted"},
		{.sig = SIGQUIT, .rtn = 131, .msg = "Quit"},
		{.sig = SIGILL, .rtn = 132, .msg = "Illegal instruction"},
		{.sig = SIGTRAP, .rtn = 133, .msg = "Trace/BPT trap"},
		{.sig = SIGABRT, .rtn = 134, .msg = "Abort"},
	//	{.sig = SIGEMT, .rtn = 135, .msg = "emulate instruction executed"},
		{.sig = SIGFPE, .rtn = 136, .msg = "Floating exception"},
		{.sig = SIGKILL, .rtn = 137, .msg = "Killed"},
		{.sig = SIGBUS, .rtn = 138, .msg = "Bus error"},
		{.sig = SIGSEGV, .rtn = 139, .msg = "Segmentation fault"},
		{.sig = SIGSYS, .rtn = 140, .msg = "Bad system call"},
		{.sig = SIGPIPE, .rtn = 141, .msg = "Broken pipe"},
		{.sig = SIGALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGTERM, .rtn = 143, .msg = "Terminated"},
		{.sig = SIGURG, .rtn = 0, .msg = ""},
		{.sig = SIGSTOP, .rtn = 0, .msg = "Suspended"},
		{.sig = SIGTSTP, .rtn = 0, .msg = "Suspended"},
		{.sig = SIGCONT, .rtn = 0, .msg = "Continued"},
		{.sig = SIGCHLD, .rtn = 0, .msg = "Done"},
		{.sig = SIGTTIN, .rtn = 0, .msg = "background read attempted from control terminal"},
		{.sig = SIGTTOU, .rtn = 0, .msg = "background write attempted from control terminal"},
		{.sig = SIGIO, .rtn = 0, .msg = "I/O is possible on a descriptor"},
		{.sig = SIGXCPU, .rtn = 152, .msg = "Cputime limit exceeded"},
		{.sig = SIGXFSZ, .rtn = 153, .msg = "Filesize limit exceeded"},
		{.sig = SIGVTALRM, .rtn = 142, .msg = "Alarm clock"},
		{.sig = SIGPROF, .rtn = 155, .msg = "Profiling time alarm"},
		{.sig = SIGUSR1, .rtn = 158, .msg = "User signal 1"},
		{.sig = SIGUSR2, .rtn = 159, .msg = "User signal 2"},
		{.msg = NULL}
};

static void	ft_signal_check(t_process *p)
{
 	if (WIFSTOPPED(p->ret))
		p->status = SUSPENDED;
	else if (WIFCONTINUED(p->ret))
		p->status = RUNNING_FG;
	else
		p->status = KILLED;
	p->ret = g_signal_msg[WTERMSIG(p->ret) - 1].rtn;
}

void	ft_wait(t_process *p, t_shell *sh)
{
	int prompt;
	(void)sh;

	prompt = 0;
	ft_printf("WAIT\n");
	while (p)
	{
		if ((p->pid == 0
				|| (p->status == SUSPENDED && waitpid(p->pid , &p->ret, WNOHANG))
				|| (p->status == RUNNING_FG && waitpid(p->pid, &p->ret, WUNTRACED) > 0)
			 	|| (p->status == RUNNING_BG && waitpid(p->pid, &p->ret, WUNTRACED ) > 0))
				&& IS_RUNNING(p->status))
		{
			if (p->ret > 0 && WIFEXITED(p->ret))
			{
				p->ret =  WEXITSTATUS(p->ret);
				p->status = DONE;
			}
			else if (WIFSIGNALED(p->ret))
				ft_signal_check(p);
			else 
				p->status = DONE;
			if (prompt)
				ft_put_process(p);
		}
		p = p->grp;
	}
}

void ft_wait_background(t_shell *sh)
{
	t_process *tmp;

	tmp = sh->process;
	while (tmp)
	{
		if (tmp->status == RUNNING_BG)
			ft_wait(tmp, sh);
		tmp = tmp->next;
	}
}

