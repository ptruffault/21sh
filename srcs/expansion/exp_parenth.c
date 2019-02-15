/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parenth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:48:27 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 15:48:29 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static char	*handle_modifier(char *parenth, char *ptr, t_shell *sh, char *val2)
{
	char *val;
	char *val1;

	val = NULL;
	val1 = ft_get_secondvalue(parenth);
	if (*ptr == '-' && !(val = ft_strdup(get_tenvv_val(sh->env, val1))))
		val = ft_strdup(val2);
	if (*ptr == '+')
		val = (get_tenvv(sh->env, val1) ? ft_strdup(val2) : NULL);
	if (*ptr == '?' && !(val = ft_strdup(get_tenvv_val(sh->env, val1))))
		error(val1, val2);
	if (*ptr == '=' && !(val = ft_strdup(get_tenvv_val(sh->env, val1)))
	&& val2 && (sh->env = ft_new_envv(sh->env, val1, val2)))
		val = ft_strdup(val2);
	ft_strdel(&val1);
	return (val);
}

char *ft_strswap(char *s1, char *s2)
{
	ft_strdel(&s1);
	return (s2);
}

char	*ft_get_param_value(t_shell *sh, char *parenth)
{
	int i;
	char *val;
	char *param;

	i = 0;
	val = NULL;
	while (parenth && parenth[i])
	{
		if (parenth[i] == ':')
		{
			if (!ft_strchr("-+?=", parenth[i + 1]))
				error_c("unrecognized modifier", parenth[i + 1]);
			else if ((param = ft_get_secondvalue(&parenth[i + 2])))
			{
				if (val)
					ft_strdel(&val);
				val = handle_modifier(parenth, &parenth[i + 1], sh, param);
				ft_strdel(&param);
			}
		}
		else if (parenth[i] == '#' || parenth[i] == '%')
		{
			if (!val)
			{
				param =  ft_get_secondvalue(parenth);
				val = ft_strdup(get_tenvv_val(sh->env, param));
				ft_strdel(&param);
			}
			val = ft_cut_string(parenth, val, &i);
		}
		i++;
	}
	if (!val)
		val = ft_strdup(get_tenvv_val(sh->env, parenth));
	return (val);
}

static char	*ft_exp_end(char *ret, char *ptr, char *value, char *parenth)
{
	char *tmp;

	tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 2, value);
	ft_strdel(&ret);
	ft_strdel(&value);
	ft_strdel(&parenth);
	return (tmp);
}

static char	*ft_get_len(char *value)
{
	char *tmp;

	tmp = ft_itoa(ft_strlen(value));
	ft_strdel(&value);
	return (tmp);
}

char		*ft_exp_param(char *ret, t_shell *sh, char *ptr)
{
	char	*value;
	char	*tmp;
	char	*parenth;
	int		len;

	value = NULL;
	len = 0;
	if ((parenth = ft_strsub(ret, ptr - ret + 2, get_content_size(ptr))))
	{
		if (*parenth == '#')
		{
			tmp = ft_strdup(parenth + 1);
			ft_strdel(&parenth);
			len = 1;
			parenth = tmp;
		}
		if ((value = ft_get_param_value(sh, parenth)))
			ft_strdel(&parenth);
		if (len == 1)
			value = ft_get_len(value);
	}
	return (ft_exp_end(ret, ptr, value, parenth));
}
