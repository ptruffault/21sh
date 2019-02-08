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

static char	*handle_modifier(char *parenth, char *ptr, t_shell *sh)
{
	char *val;
	char *val1;
	char *val2;

	val = NULL;
	val1 = ft_strsub(parenth, 0, ptr - parenth - 1);
	val2 = ft_strdup(ptr + 1);
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
	ft_strdel(&val2);
	return (val);
}

static char	*ft_get_param_value(t_shell *sh, char *parenth)
{
	char *ptr;
	char *val;

	val = NULL;
	if (parenth && (ptr = ft_strchr(parenth, ':')) && ++ptr)
	{
		if (!ft_strchr("-+?=", *ptr))
			error_c("unrecognized modifier", *ptr);
		else if (!(val = handle_modifier(parenth, ptr, sh)))
			return (NULL);
		return (val);
	}
	else if (parenth)
		val = ft_strdup(get_tenvv_val(sh->env, parenth));
	return (val);
}

static char	*ft_exp_end(char *ret, char *ptr, char *value)
{
	char *tmp;

	tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 2, value);
	ft_strdel(&ret);
	ft_strdel(&value);
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
		parenth = ft_exp_param_sub(parenth, sh);
		if ((value = ft_get_param_value(sh, parenth)))
			ft_strdel(&parenth);
		if (len == 1)
			value = ft_get_len(value);
	}
	return (ft_exp_end(ret, ptr, value));
}
