/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:48:31 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/04 11:48:33 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

void	ft_exec_son(t_process *p, t_tree *t, t_shell *sh)
{
	if (!t->r || (t->r && ft_redirect_builtin(t, p)))
	{
		if (p->builtins == TRUE)
			run_builtin(t, p->argv, sh);
		else if (p->cmd && !ft_isempty(p->cmd))
		{
			execve(p->cmd, p->argv, p->env);
			error("execve fucked up", p->cmd);
		}
		else
			error("command not found", *p->argv);
	}
}
