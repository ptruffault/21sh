/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_tparam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:30:21 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/04 16:30:23 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int		ft_tools_2(char *src)
{
	int i;

	i = 0;
	while (ft_isdigit(src[i]))
		i++;
	return (i);
}

static t_param	*ft_read(char *ptr, t_param *p)
{
	int i;

	i = 0;
	while (ptr[i] != '\0' && (ft_strchr("#0 +-", ptr[i])))
		p->flag = ft_stradd_char(p->flag, ptr[i++]);
	p->width = (ft_isdigit(ptr[i]) ? ft_atoi(&ptr[i]) : p->width);
	i = i + ft_tools_2(&ptr[i]);
	if (ptr[i] == '.')
	{
		while (ptr[i] == '.')
			i++;
		p->precision = (ft_isdigit(ptr[i]) ? ft_atoi(&ptr[i]) : 0);
		i = i + ft_tools_2(&ptr[i]);
	}
	while (ptr[i] != '\0' && (ft_strchr("lhjtz", ptr[i])))
		p->length = ft_stradd_char(p->length, ptr[i++]);
	p->spec = (TEST_SPEC(ptr[i]) ? ptr[i++] : '?');
	p->opts_len = p->opts_len + i;
	return (p);
}

t_param			*read_option(char *format, va_list *ap, t_param *p)
{
	p->opts_len = 1;
	if (!(TEST(*(format + 1))) || format + 1 == 0)
		return (p);
	while (p->spec == '?' && TEST(*(format + p->opts_len))
	&& *(format + p->opts_len) != '\0')
		p = ft_read(format + p->opts_len, p);
	p->value = (p->spec != '?' ? ftp_get_value(p, ap) : NULL);
	p->var_len = ft_strlen(p->value) + p->exep;
	return (p);
}
