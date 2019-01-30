/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:19 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

pid_t ft_execve(t_process *p, t_tree *t)
{
	pid_t pid;

	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", p->cmd);
	else if (pid == 0)
	{
		ft_redirect(t);
		execve(p->cmd, p->argv, p->env);
		warning("execve fucked up", p->cmd);
	}
	return (pid);
}


//t_process -> env argv  redirect{fd[3]} binpath         pid  


t_process *init_process(t_tree *t)
{
	 t_process *new;

	new = NULL;
	if ((new = (t_process *)malloc(sizeof(t_process))))
	{
		if (t->o_type == O_BACK)
			new->status = RUNNING_BG;
		else
			new->status = RUNNING_FG;
		new->ret = -1;
		new->next = NULL;
		new->pid = 0;
		if (!(new->argv = ft_twordto_arr(t->cmd)))
		{
			free(new);
			return (NULL);
		}
	}
	return (new);
}

int ft_exec(t_tree *t)
{
	t_process *p;
	t_shell *sh;

	
	sh = ft_get_set_shell(NULL);
	if ((p = init_process(t)))
	{
		if (check_builtin(*p->argv))
			p->ret = run_builtin(t, p->argv);
		else if ((p->cmd = get_bin_path(*p->argv, sh->env)))
		{
			p->env = tenvv_to_tab(sh->env);
			p->pid = ft_execve(p, t);
			ft_add_process(sh, p);
			if (sh->process->status == RUNNING_FG)
			{
				wait(&p->ret);
				p->status = DONE;
			}
		}
	}
	return (p->ret);
}
