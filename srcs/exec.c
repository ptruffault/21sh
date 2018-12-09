/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:26:09 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/05 13:26:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static t_envv *next_instruction(t_tree *t, t_envv  *e)
{
	if (t->o_type && t->next->arr)
	{
		if (t->o_type == O_SEP)
			return (exec_instruction(t->next, e));
		if (t->o_type == O_AND)
		{
			if (t->ret == 0)
				return (exec_instruction(t->next, e));
			else
				while (t && t->o_type == O_AND)
					t = t->next;
		}	
		if (t->o_type == O_OR)
		{
			if (t->ret != 0)
				return (exec_instruction(t->next, e));
			else
				while (t && t->o_type == O_OR)
					t = t->next;
		}
	}
	return (e);
}

t_envv *ft_exec(t_tree *t, t_envv *envv, t_redirect *r)
{
	char **e;
	pid_t pid;
	char *bin_path;

	if (r)
		return(ft_exec_redirection(t, envv, r));
	if (check_builtin(t->arr))
		return (run_builtin(t, envv));
	if (!(bin_path = get_bin_path(*t->arr, envv)))
	{
		error("unknow cmd", *t->arr);
		t->ret = -1;
		return (envv);
	}
	e = tenvv_to_tab(envv);
	if ((pid = fork()) == -1)
		warning("fork failed to create a new process", *t->arr);
	if (pid == 0 && execve(bin_path, t->arr, e) == -1)
		warning("execve fucked up", *t->arr);
	ft_freestrarr(e);
	ft_strdel(&bin_path);
	wait(&t->ret);
	return (envv);
}

t_envv *exec_instruction(t_tree *t, t_envv *e)
{
	t_redirect *save;

	if (!t || !t->arr)
		return (e);
	save = t->r;
	if (t->o_type == O_PIPE && t->next && t->next->arr)
		e = exec_pipe(t, e);
	else
		e = ft_exec(t, e, t->r);
	t->r = save;
	return (next_instruction(t, e));
}
