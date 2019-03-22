/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:06 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static void			ft_init_fd(t_process *ret, t_shell *sh)
{
	ret->fd[0] = sh->std[0];
	ret->fd[1] = sh->std[1];
	ret->fd[2] = sh->std[2];
	ret->pgid = 0;
	ret->pipe[0] = -1;
	ret->pipe[1] = -1;
	ret->status = INIT;
	ret->ret = -1;
	ret->argv = NULL;
	ret->grp = NULL;
	ret->next = NULL;
	ret->pid = -1;
	ret->env = NULL;
	ret->builtins = FALSE;
}

static t_process	*ft_abort(t_process *p, char *err, t_process *tmp)
{
	t_process *head;

	head = p;
	error(err, *tmp->argv);
	while (p && p->cmd)
	{
		if (p->grp)
		{
			ft_close(p->pipe[0]);
			ft_close(p->pipe[1]);
		}
		p = p->grp;
	}
	return (ft_free_tprocess(head));
}

t_process			*init_process(t_tree *t, t_shell *sh)
{
	t_process	*ret;

	ret = NULL;
	if ((ret = (t_process *)malloc(sizeof(t_process))))
	{
		ft_init_fd(ret, sh);
		if (!(ret->argv = ft_twordto_arr(t->cmd)))
		{
			free(ret);
			return (ret = NULL);
		}
		if (check_builtin(*ret->argv))
		{
			ret->builtins = TRUE;
			if (!(ret->cmd = ft_strdup(*ret->argv)))
				return (ft_free_tprocess(ret));
		}
		else
		{
			ret->env = tenvv_to_tab(sh->env);
			if ((ret->cmd = get_bin_path(*ret->argv, sh->env)))
			{
				sh->env = ft_new_envv(sh->env, "_", ret->cmd);
				
			}
		}
	}
	return (ret);
}

t_process *init_pipe_process(t_tree *t, t_shell *sh)
{
	t_process *head;
	t_process *tmp;

	head = NULL;
	if ((head = init_process(t, sh)) && !pipe(head->pipe))
	{
		tmp = head;
		if (!head->cmd)
			return (ft_abort(head, "command not found", head));
		while (t->o_type == O_PIPE)
		{	
			t = t->next;
			if (t && (tmp->grp = init_process(t, sh)))
		 	{
		 		tmp = tmp->grp;
		 		if (tmp->cmd)
		 		{
		 			if (t->o_type == O_PIPE && t->next 
		 				&& (pipe(tmp->pipe) < 0))
						return (ft_abort(head, "broken pipe", tmp));
		 		}
		 		else
		 			return (ft_abort(head, "command not found", tmp));
			}
		}
	}
	return (head);
}
