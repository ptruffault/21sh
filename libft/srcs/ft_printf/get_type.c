/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 13:49:46 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/09 13:49:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

char				get_char(va_list *ap)
{
	int c;

	c = va_arg(*ap, int);
	while (c < -128 || c > 127)
		c = c - 256;
	return (c);
}

unsigned char		get_uchar(va_list *ap)
{
	unsigned int c;

	c = va_arg(*ap, unsigned int);
	while (c > 255)
		c = c - 256;
	return ((unsigned char)c);
}

intmax_t			get_ent(va_list *ap, t_param *p)
{
	intmax_t ret;

	if (TEST_FLAG(p->length, 'j'))
		ret = (intmax_t)va_arg(*ap, intmax_t);
	else if (TEST_FLAG(p->length, 'z'))
		ret = (size_t)va_arg(*ap, size_t);
	else if (TEST_2OPTS(p->length, 'l'))
		ret = (signed long long int)va_arg(*ap, signed long long int);
	else if (TEST_FLAG(p->length, 'l') || p->spec == 'D')
		ret = (signed long int)va_arg(*ap, signed long int);
	else if (TEST_FLAG(p->length, 'h'))
		ret = (signed short int)va_arg(*ap, signed int);
	else if (TEST_2OPTS(p->length, 'h'))
		ret = (signed char)get_char(ap);
	else
		ret = va_arg(*ap, int);
	if (ret < 0)
	{
		ret = -ret;
		p->signe = '-';
	}
	else if (TEST_FLAG(p->flag, '+'))
		p->signe = '+';
	return (ret);
}

uintmax_t			get_uent(va_list *ap, t_param *p)
{
	uintmax_t ret;

	if (TEST_FLAG(p->length, 'z'))
		return ((size_t)va_arg(*ap, size_t));
	else if (TEST_FLAG(p->length, 'j'))
		return ((uintmax_t)va_arg(*ap, uintmax_t));
	else if (TEST_2OPTS(p->length, 'h'))
		return ((unsigned char)get_uchar(ap));
	else if (TEST_FLAG(p->length, 'h') && p->spec != 'U')
		return ((unsigned short int)va_arg(*ap, unsigned int));
	else if (TEST_2OPTS(p->length, 'l'))
		return ((unsigned long long int)va_arg(*ap, unsigned long long int));
	else if (TEST_FLAG(p->length, 'l') || p->spec == 'O' || p->spec == 'U')
		return ((unsigned long int)va_arg(*ap, unsigned long int));
	else
		return (va_arg(*ap, unsigned int));
	return (ret);
}
