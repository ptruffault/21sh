/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_startwith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:24:09 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 16:24:10 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_str_startwith(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int		ft_str_endwith(char *s1, char *s2)
{
	int i;
	int j;

	if (s1 && s2)
	{
		j = 0;
		i = (int)ft_strlen(s1) - (int)ft_strlen(s2);
		while (i > 0 && s1[i] && s2[j])
		{
			if (s1[i++] != s2[j++])
				return (0);
		}
		if (s1[i] == 0 && s2[j] == 0)
			return (1);
	}
	return (0);
}
