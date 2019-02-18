/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uintmax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:41:39 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:41:43 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	f(uintmax_t value, unsigned int base, char *str, int *i)
{
	char	*tmp;

	tmp = "0123456789abcdef";
	if (value >= base)
		f(value / base, base, str, i);
	str[*i] = tmp[value % base];
	(*i)++;
}

char		*ft_itoa_base_u(uintmax_t value, int base)
{
	int		i;
	char	*str;

	i = 0;
	if (base < 2 || base > 16)
		return (NULL);
	if (value == 0)
		return (ft_strdup("0"));
	if (value == 1)
		return (ft_strdup("1"));
	if (!(str = (char*)malloc(32)))
		return (NULL);
	f(value, base, str, &i);
	str[i] = '\0';
	return (str);
}
