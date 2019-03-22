/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:15:32 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

char	*ft_strappend(char **str, const char *end)
{
	char	*rtn;

	rtn = ft_strjoin(*str, end);
	ft_strdel(str);
	*str = rtn;
	return (rtn);
}

char	*heredoc_get_input(char *eoi, t_shell *sh)
{
	char	*ret;
	char	*in;
	int d;

	ret = NULL;
	in = NULL;
	d = 0;
	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	if (get_input(&in))
	{
		while (!ft_strequ(in, eoi) && sh->heredoc == 1)
		{
			if (!(in = ft_strappend(&in, "\n")) || !(ret = ft_strappend(&ret, in)))
				break ;
			ft_putstr("\033[00;34mheredoc>\n\033[00m");
			if ((d = get_input(&in)) == 4)
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
