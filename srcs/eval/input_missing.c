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

#include "../../includes/21sh.h"

char	*heredoc_get_input(char *eoi)
{
	char	*ret;

	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	ret = get_input();
	if (!ft_strequ(ret, eoi))
		return (ft_strjoin_fr(ft_stradd_char(ret, '\n')
		, heredoc_get_input(eoi)));
	else
		return (NULL);
}
