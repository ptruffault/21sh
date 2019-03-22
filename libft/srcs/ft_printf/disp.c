/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:36:45 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 15:36:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_puttparam(t_param *p, int ret)
{
	if (p->width > p->var_len && !(TEST_FLAG(p->flag, '-')))
	{
		ft_putnchar(' ', p->width - p->var_len - (p->spec == '?' ? 1 : 0));
		ret = ret + p->width - p->var_len - (p->spec == '?' ? 1 : 0);
	}
	else if (TEST_FLAG(p->flag, ' ') && TEST_SIGN(p->spec) && p->signe == '?')
	{
		ft_putchar(' ');
		ret++;
	}
	if (p->spec != '?')
	{
		ft_putstr(p->value);
		if (p->exep == 1)
			ft_putchar('\0');
		ret = ret + ft_strlen(p->value) - 1 + p->exep;
	}
	else
		ret--;
	if (TEST_FLAG(p->flag, '-') && p->width > p->var_len)
	{
		ft_putnchar(' ', p->width - p->var_len);
		ret = ret + p->width - p->var_len;
	}
	return (ret);
}

int	print(char *format, t_param *p)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			ret = ft_puttparam(p, ret);
			i = i + p->opts_len;
			p = p->next;
		}
		else
			ft_putchar(format[i++]);
		ret++;
	}
	return (ret);
}
