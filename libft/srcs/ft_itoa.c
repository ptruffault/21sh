/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:10:44 by ptruffau          #+#    #+#             */
/*   Updated: 2017/11/16 13:11:55 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_length_nbr(int nb)
{
	int i;

	i = 1;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int nbr)
{
	char	*res;
	int		len;
	int		neg;

	neg = (nbr < 0) ? 1 : 0;
	len = ft_length_nbr(nbr);
	if (len == 1 && nbr == 0)
		len++;
	if (!(res = (char*)malloc(sizeof(char) * (len + neg))))
		return (NULL);
	res[--len + neg] = '\0';
	if (neg > 0)
		res[0] = '-';
	while (--len >= 0)
	{
		if (nbr < 0)
			res[len + neg] = -(nbr % 10) + '0';
		else
			res[len + neg] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (res);
}
