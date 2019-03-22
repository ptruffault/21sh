/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:36:45 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 15:36:47 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char				*parse_spec_again(t_param *p, va_list *ap)
{
	char	*ret;
	int		r;

	ret = NULL;
	if (p->spec == 'C' || (p->spec == 'c' && TEST_FLAG(p->length, 'l')))
	{
		ret = ft_wchar(va_arg(*ap, wchar_t));
		p->exep = (*ret == 0 ? 1 : 0);
		return (ret);
	}
	else if (p->spec == 'c' || (p->spec == 'C' && TEST_FLAG(p->length, 'h')))
	{
		r = get_char(ap);
		p->exep = (r == 0 ? 1 : 0);
		return (ft_char_to_str((char)r));
	}
	else if (p->spec == '%')
		return (ft_char_to_str('%'));
	return (NULL);
}

char					*parse_spec(t_param *p, va_list *ap)
{
	int *ret;

	if (p->spec == 'd' || p->spec == 'i' || p->spec == 'D')
		return (ft_itoa_base(get_ent(ap, p), 10));
	if (p->spec == 'o' || p->spec == 'O')
		return (ft_itoa_base_u(get_uent(ap, p), 8));
	if (p->spec == 'u' || p->spec == 'U')
		return (ft_itoa_base_u(get_uent(ap, p), 10));
	if (p->spec == 'x')
		return (ft_itoa_base_u(get_uent(ap, p), 16));
	if (p->spec == 'X')
		return (ft_strmap_i(ft_itoa_base_u(get_uent(ap, p), 16), ft_toupper));
	if (p->spec == 'p')
		return (ft_itoa_base_u(va_arg(*ap, uintmax_t), 16));
	if (p->spec == 'S' || (p->spec == 's' && TEST_FLAG(p->length, 'l')))
	{
		if (!(ret = va_arg(*ap, int *)))
			return (NULL);
		return (ft_wstr(ret));
	}
	if (p->spec == 's')
		return (ft_strdup(va_arg(*ap, char *)));
	return (parse_spec_again(p, ap));
}
