/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:36:22 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/04 17:36:24 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char	*get_flag_zero(t_param *p, char *ret)
{
	int i;

	if (!TEST_FLAG(p->flag, '0') || TEST_FLAG(p->flag, '-'))
		return (ret);
	i = p->width - p->var_len - (p->signe != '?' ? 1 : 0);
	i = i - TEST_FLAG(p->flag, ' ') - p->exep;
	if (p->precision != -1 && TEST_SPEC_NBR(p->spec))
		return (ret);
	if (i > 0)
		return(my_strjoin(ft_strnew_nchar('0', i), ret));
	return (ret);
}

static char	*get_prefix(t_param *p, char *tmp_val)
{
	char *ret;
	char *tmp;

	ret = NULL;
	tmp = NULL;
	p->var_len = ft_strlen(tmp_val);
	if (TEST_FLAG(p->flag, '#') || p->spec == 'p')
		tmp = get_ox(p, tmp_val);
	if (p->precision != -1 && p->precision > p->var_len
	&& TEST_SPEC_NBR(p->spec))
	{
		ret = my_strjoin(ft_strnew_nchar('0', p->precision - p->var_len
		+ (p->spec == 'p' ? 2 : 0)), ret);
		p->var_len = ft_strlen(ret) + ft_strlen(tmp_val);
	}
	if (p->var_len < (p->precision < 1 ? p->width : p->precision))
		ret = get_flag_zero(p, ret);
	if (TEST_FLAG(p->flag, '#') || p->spec == 'p')
		ret = my_strjoin(tmp, ret);
	if (p->signe != '?')
		ret = my_strjoin(ft_char_to_str(p->signe), ret);
	p->var_len = p->var_len + ft_strlen(ret);
	return (ret);
}

char		*ftp_get_value(t_param *p, va_list *ap)
{
	char *prefix;
	char *s;
	char *tmp_val;

	tmp_val = parse_spec(p, ap);
	prefix = get_prefix(p, tmp_val);
	if (!tmp_val && TEST_STR(p->spec) && !prefix)
		tmp_val = ft_strdup("(null)");
	if (p->precision < p->var_len && p->precision != -1 && TEST_STR(p->spec))
		tmp_val = ft_strndup_fr(tmp_val, p->precision);
	if (TEST_SPEC_NBR(p->spec) && !TEST_FLAG(p->flag, '0')
 	&& p->precision == 0 && ft_atoi(tmp_val) == 0 && !(TEST_FLAG(p->flag, '#')
 	&& (p->spec == 'o' || p->spec == 'O')))
	{
		ft_strdel(&tmp_val);
		return (prefix);
	}
	if (*tmp_val == '-')
	{
		s = ft_strdup(&tmp_val[1]);
		ft_strdel(&tmp_val);
		tmp_val = s;
	}
	return (my_strjoin(prefix, tmp_val));
}
