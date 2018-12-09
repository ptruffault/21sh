/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:57:50 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/03 12:57:51 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

t_tree		*ft_get_set_tree(t_tree *new_t)
{
	static t_tree	*stored_t = NULL;

	if (new_t)
		stored_t = new_t;
	return (stored_t);
}

void abort_exit(int s)
{
	(void)s;
	ft_free_tenvv(ft_get_set_envv(NULL));
	ft_free_tree(ft_get_set_tree(NULL));
	error("21sh aborted", NULL);
	exit(0);

}

void	set_signals(void)
{

	if (signal(SIGINT, abort_exit) == SIG_ERR
	|| signal(SIGHUP, abort_exit) == SIG_ERR
	|| signal(SIGHUP, abort_exit) == SIG_ERR
	|| signal(SIGTERM, abort_exit))
		warning("SIGNAL SETTING ERROR", NULL);
/*	
	signal(SIGTERM, abort_exit);
	signal(SIGSEGV, abort_exit);
	signal(SIGQUIT, abort_exit);
	signal(SIGFPE, abort_exit);
	signal(SIGALRM, abort_exit);
	signal(SIGKILL, abort_exit);
	signal(SIGABRT, abort_exit);
	signal(SIGUSR1, abort_exit);
	signal(SIGUSR2, abort_exit);*/
	ft_putstr("OK");
}
