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
	char	*in;

	ret = NULL;
	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	if ((in = get_input()))
	{
		while (!ft_strequ(in, eoi) && sh->heredoc == 1)
		{
			in = ft_stradd_char(in, '\n');
			ret = ft_strjoin_fr(ret, in);
			ft_putstr("\033[00;34mheredoc>\n\033[00m");
			if (!(in = get_input()))
			{
				ft_strdel(&in);
				ft_strdel(&ret);
				return (NULL);
			}
		}
		ft_strdel(&in);
	}
	return (ret);
}
