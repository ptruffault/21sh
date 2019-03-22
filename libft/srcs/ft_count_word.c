/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:05:10 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:05:11 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_count_word(char *s)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		if (ft_isspace(s[i]) && !(ft_isspace(s[i - 1])))
			n++;
		i++;
	}
	if (!(ft_isspace(s[i - 1])) && !s[i])
		n++;
	return (n);
}
