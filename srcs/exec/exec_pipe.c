/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:53:23 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 13:51:14 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

void		ft_execv_son(t_process *p, t_shell *sh, t_tree *t)
{
	char	**env;

	if (ft_redirect_builtin(t, p))
	{
		if (!p->cmd)
			error("unknow command",t->cmd->word);
		else if (p->builtins == TRUE)
			p->ret = run_builtin(t, p->argv);
		else if (p->cmd)
		{
			env = tenvv_to_tab(sh->env);
			execve(p->cmd, p->argv, env);
			warning("execve fucked up", p->cmd);
			ft_freestrarr(env);
		}
	}
}

void ft_exec_son(t_process *p, t_shell *sh, t_tree *t)
{
	ft_execv_son(p, sh ,t);
	if (p->status == RUNNING_FG)
	{
		if (p->builtins == FALSE)
			wait(&p->ret);
		if (p->status != KILLED)
			p->status = DONE;
	}
}

static t_tree	*ft_end_of_pipe(t_tree *t, t_process *p1, t_process *p2, int pipes[2])
{
	ft_close(pipes[0]);
	ft_close(pipes[1]);
	if (p1 && p2 && p1->pid > 0 && p2->pid > 0)
	{
		waitpid(p1->pid, &p1->ret, 0);
		p1->status = DONE;
		waitpid(p2->pid, &p2->ret, 0);
		p2->status = DONE;
	}
	while (t->o_type == O_PIPE)
		t = t->next;
	return (t);
}

static void		ft_exec_next(t_tree *t, int pipes[2], t_shell *sh, t_process *p)
{
	int ret;

	dup2(pipes[0], STDIN_FILENO);
	ft_close(pipes[1]);
	if (t->next->o_type == O_PIPE && t->next->next)
	{
		exec_pipe(t->next);
		ret = t->next->ret;
	}
	else
		ft_exec_son(p, sh, t);
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	exit(ret);
}

static void		ft_exec_first(t_tree *t, t_process *p, int pipes[2], t_shell *sh)
{
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[0]);
	ft_exec_son(p, sh, t);
	ft_free_tshell(sh);
	ft_free_tree(ft_get_set_tree(NULL));
	exit(p->ret);
}

t_tree			*exec_pipe(t_tree *t)
{
	int			pipes[2];
	t_process	*p1;
	t_process	*p2;
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (pipe(pipes) != 0)
		return (t);
	p1 = NULL;
	p2 = NULL;
	if (!(p1 = init_process(t, sh)) || (p1->pid = fork()) < 0)
		return (ft_end_of_pipe(t, p1, p2, pipes));
	else if (p1->pid == 0)
		ft_exec_first(t, p1, pipes, sh);
	if (!(p2 = init_process(t->next, sh)) || (p2->pid = fork()) < 0)
		return (ft_end_of_pipe(t, p1, p2, pipes));
	else if (p2->pid == 0)
		ft_exec_next(t, pipes, sh, p2);
	return (ft_end_of_pipe(t, p1, p2, pipes));
}
