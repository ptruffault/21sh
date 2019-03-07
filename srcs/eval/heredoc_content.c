/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:15:32 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/08 14:18:42 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

char	*heredoc_get_input(char *eoi, t_shell *sh)
{
	char	*ret;

	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	ret = get_input();
	if (!ft_strequ(ret, eoi) && sh->heredoc == 1)
		return (ft_strjoin_fr(ft_stradd_char(ret, '\n'),
		heredoc_get_input(eoi, sh)));
	else if (sh->heredoc != -1)
		sh->heredoc = 0;
	ft_strdel(&ret);
	return (NULL);
}
