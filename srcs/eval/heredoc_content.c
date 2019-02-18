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

char	*heredoc_get_input(char *eoi)
{
	char	*ret;
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	sh->heredoc = 1;
	ret = get_input();
	if (!ft_strequ(ret, eoi) && sh->heredoc == 1)
		return (ft_strjoin_fr(ft_stradd_char(ret, '\n')
		, heredoc_get_input(eoi)));
	else
	{
		sh->heredoc = 0;
		return (ret);
	}
}
