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
	char	*hi_path;

	if (sh->e.input[0] != '\0'
	&& (hi_path = get_tenvv_val(sh->env, "HISTORY")))
	{
		ft_write_in_file(hi_path, sh->e.input);
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

char		*get_input(void)
{
	t_shell			*sh;
	unsigned long	buf;

	if (!isatty(0))
		return (NULL);
	sh = ft_get_set_shell(NULL);
	sh->e = init_tedit(sh);
	ft_setup_edit_term(sh);
	while (sh->e.edited == FALSE)
	{
		buf = 0;
		read(0, &buf, 8);
		buf = handle_input(buf, &sh->e);
		if (buf == 0)
		{
			return (NULL);
		}
		ft_print_line(&sh->e);
	}
	return (ft_update_hist(sh));
}
