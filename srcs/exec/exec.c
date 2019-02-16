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

#include "../../includes/shell42.h"

static t_tree	*next_instruction(t_tree *t)
{
	unsigned int tmp;

	if (t->o_type && t->next)
	{
		if (t->o_type == O_SEP || t->o_type == O_BACK)
			return (t->next);
		if (t->o_type == O_AND || t->o_type == O_OR)
		{
			if ((t->o_type == O_AND && t->ret == 0)
			|| (t->o_type == O_OR && t->ret != 0))
				return (t->next);
			else
			{
				tmp = t->o_type;
				while (t->next && (t->o_type == tmp || t->o_type == O_PIPE))
					t = t->next;
				return (t->next);
			}
		}
	}
	return (NULL);
}

t_tree			*exec_instruction(t_tree *t)
{
	t_process	*p;
	t_shell		*sh;

	sh = ft_get_set_shell(NULL);
	if (t->o_type == O_PIPE && t->next)
		t = exec_pipe(t);
	else if ((p = init_process(t, sh)))
	{
		p->next = sh->process;
		sh->process = p;
		if (t->r && ft_redirect_builtin(t, p->fd) == -1)
			warning("redirection fucked up", NULL);
		t->ret = ft_exec(t, p);
		ft_reset_fd(p->fd);
	}
	return (t);
}

t_tree			*exec_tree(t_tree *t)
{
	t_tree *tmp;

	tmp = t;
	while (tmp)
	{
		if (!tmp->cmd || !tmp->cmd->word)
		{
			if (tmp->o_type == O_SEP || tmp->o_type == 0
			|| tmp->o_type == O_BACK)
				tmp = tmp->next;
			else
			{
				error("syntax error near", tmp->next->cmd->word);
				break ;
			}
		}
		else
		{
			tmp = exec_instruction(tmp);
			tmp = next_instruction(tmp);
		}
	}
	return (t);
}
