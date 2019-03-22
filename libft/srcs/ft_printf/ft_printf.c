/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:36:45 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 15:36:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_printf(char *format, ...)
{
	va_list ap;
	t_param *p;
	int		ret;

	p = NULL;
	va_start(ap, format);
	p = init_tparam(format, &ap);
	ret = print(format, p);
	free_tparam(p);
	va_end(ap);
	return (ret);
}
