/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:12:58 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/09 11:21:33 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

char		*ft_update_hist(t_shell *sh)
{
	char	*ret;

	if (sh->e.input[0] != '\0')
	{
		ft_write_in_file(get_tenvv_val(sh->env, "HISTORY"), sh->e.input);
		sh->hist = add_hist(sh->hist, sh->e.input);
	}
	sh->e.curr = ft_strlen(sh->e.input);
	ft_print_line(&sh->e);
	ret = ft_strdup(sh->e.input);
	ft_set_old_term(sh);
	free_tedit(&sh->e);
	term_actions("ve");
	ft_putchar('\n');
	return (ret);
}

static char	*dumb_term(t_shell *sh)
{
	ft_free_tshell(sh);
	error("No termcaps, so not working, so exiting", NULL);
	ft_putendl_fd("\033[00;31m21sh get killed\033[00m", 2);
	free_tedit(&sh->e);
	exit(0);
}

char		*get_input(void)
{
	t_shell			*sh;
	unsigned long	buf;

	sh = ft_get_set_shell(NULL);
	sh->e = init_tedit(sh);
	if (!(ft_setup_edit_term(sh)))
		return (dumb_term(sh));
	while (sh->e.edited == FALSE)
	{
		buf = 0;
		read(0, &buf, 8);
		buf = handle_input(buf, &sh->e);
		ft_print_line(&sh->e);
	}
	return (ft_update_hist(sh));
}
