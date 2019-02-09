/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:07:47 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/04 16:07:49 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_param	*add_tparam(void)
{
	t_param *p;

	if (!(p = (t_param *)malloc(sizeof(t_param))))
		return (NULL);
	p->flag = NULL;
	p->width = 0;
	p->precision = -1;
	p->exep = 0;
	p->spec = '?';
	p->signe = '?';
	p->value = NULL;
	p->length = NULL;
	p->var_len = 0;
	p->opts_len = 0;
	p->next = NULL;
	return (p);
}

t_param	*init_tparam(char *format, va_list *ap)
{
	int		i;
	t_param *p;
	t_param *tmp;

	p = add_tparam();
	tmp = p;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			tmp = read_option(&format[i], ap, tmp);
			i = i + tmp->opts_len;
			tmp->next = add_tparam();
			tmp = tmp->next;
		}
		else
			i++;
	}
	return (p);
}

void	free_tparam(t_param *p)
{
	t_param *tmp;

	while (p != NULL)
	{
		tmp = p->next;
		ft_strdel(&p->flag);
		ft_strdel(&p->length);
		if (p->spec != '?')
			ft_strdel(&p->value);
		free(p);
		p = NULL;
		p = tmp;
	}
}
