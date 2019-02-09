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

#include "../includes/libft.h"

static char	*ft_test(int n, int len)
{
	char	*ret;

	ret = 0;
	if (n == -2147483648)
	{
		ret = ft_strnew(11);
		ret = "-2147483648";
	}
	else
		ret = ft_strnew(len + 1);
	return (ret);
}

char		*ft_itoa(int n)
{
	int		len;
	int		buf;
	char	*ret;

	len = (n < 0) ? 1 : 0;
	buf = n;
	while (n /= 10)
		len++;
	while (n <= -10)
		len++;
	ret = ft_test(n, len);
	if (!ret)
		return (NULL);
	while (buf >= 10 || buf <= -10)
	{
		ret[len--] = (buf < 0) ? -(buf % 10) + '0' : buf % 10 + '0';
		buf /= 10;
	}
	ret[0] = (buf < 0) ? '-' : buf + '0';
	ret[1] = (buf < 0) ? -buf + '0' : ret[1];
	return (ret);
}
