/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:13:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>




int				check_builtin(char *input)
{
	char *builtins[14] = {"env", 
	"setenv", 
	"unsetenv", 
	"exit", 
	"cd", 
	"echo", 
	"export", 
	"set",
	"unset",
	"alias",
	"unalias",
	"type",
	"42",
	"jobs"
	};
	int i;

	i = 0;
	if (input == NULL)
		return (0);
	if (ft_isequal(input))
		return (1);
	while (i < 14)
		if (ft_strequ(builtins[i++], input))
			return (1);
	return (0);
}


void set_var(char **argv, t_shell *sh)
{
	t_envv *head;
	t_envv *end;
	int i;

	head = ft_setenv(new_tenvv(), argv);
	end = head;
	i = 0;
	while (end && end->next && i++)
		end = end->next;
	if (!(argv[i]))
	{
		end->next = sh->intern;
		sh->intern = head;
	}
}

void ft_jobs(t_shell *sh)
{
	t_process *tmp;
	char *stat[5] = {
		"running foreground",
		"running background",
		"done",
		"suspended",
		"killed"
	};
	int i;

	i = 0;
	tmp = sh->process;
	while (tmp)
	{
		ft_printf("[%i] %s -> %3i\t%s {%i}\n", i++, stat[tmp->status], tmp->ret, tmp->cmd,  tmp->pid);
		tmp = tmp->next;
	}
}


static t_envv	*change_envv(char **argv, t_envv *envv)
{
	t_shell *sh;
	
	if ((sh = ft_get_set_shell(NULL)))
	{	
		if (ft_strequ(*argv, "unsetenv"))
			sh->env = ft_get_set_envv(ft_unsetenv(envv, &argv[1]));
		else if (ft_strequ(*argv, "setenv"))
			sh->env = ft_get_set_envv(ft_setenv(envv, &argv[1]));
		else if (ft_strequ(*argv, "jobs"))
			ft_jobs(sh);
		else if (ft_isequal(*argv))
			set_var(argv, sh);
		else if (ft_strequ(*argv, "unset"))
			sh->intern = ft_unsetenv(sh->intern, &argv[1]);
		else if (ft_strequ(*argv, "cd"))
			sh->env = ft_get_set_envv(ft_cd(argv, envv));
		else if (ft_strequ(*argv, "export"))
			sh->env = ft_get_set_envv(ft_export(sh, &argv[1]));
		else if (ft_strequ(*argv, "set"))
			ft_puttenvv(sh->intern);
		else if (ft_strequ(*argv, "alias"))
			sh->alias = ft_setenv(sh->alias, &argv[1]);
		else if (ft_strequ(*argv, "unalias"))
			sh->alias = ft_unsetenv(sh->alias, &argv[1]);
	}
	ft_get_set_shell(sh);
	return (sh->env);
}


int run_builtin(t_tree *t, char **argv)
{
	t_envv *envv;
	int fd[3];

	fd[0] = 0;
	fd[1] =  1;
	fd[2] = 2;
	if(t->r && ft_redirect_builtin(t, fd) == -1)
		warning("redirection fucked up", NULL);
	envv = ft_get_set_envv(NULL);
	if (ft_strequ(*argv, "exit"))
		ft_exit();
	else if (ft_strequ(*argv, "env"))
		ft_env(envv, argv);
	else if (ft_strequ(*argv, "echo"))
		ft_echo(&argv[1]);
	else if (ft_strequ(*argv, "type"))
		ft_type(t->cmd->next);
	else if (ft_strequ(*argv, "42"))
		exec_file(argv[1]);
	else
		ft_get_set_envv(change_envv(argv, envv));
	if (t->r)
		ft_reset_fd(fd);
	return (0);
}

