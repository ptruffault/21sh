/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parenth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:26:29 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

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

char		*ft_get_cutted_value(char *parenth, t_shell *sh, char *val, int *i)
{
	char *param;

	if (!val)
	{
		param = ft_get_secondvalue(parenth);
		val = ft_strdup(get_tenvv_val(sh->env, param));
		ft_strdel(&param);
	}
	val = ft_cut_string(parenth, val, i);
	return (val);
}

char		*ft_get_param_value(t_shell *sh, char *parenth)
{
	int		i;
	char	*val;
	char	*param;

	i = -1;
	val = NULL;
	while (parenth && parenth[++i])
		if (parenth[i] == ':' && ft_strchr("-+?=", parenth[i + 1])
			&& (param = ft_get_secondvalue(&parenth[i + 2])))
		{
			if (val)
				ft_strdel(&val);
			val = handle_modifier(parenth, &parenth[i + 1], sh, param);
			ft_strdel(&param);
		}
		else if (parenth[i] == '#' || parenth[i] == '%')
			val = ft_get_cutted_value(parenth, sh, val, &i);
	if (!val && !(val = ft_strdup(get_tenvv_val(sh->env, parenth))))
		return (NULL);
	return (val);
}

char		*ft_exp_param(char *ret, t_shell *sh, char *ptr)
{
	char	*value;
	char	*parenth;
	int		len;

	value = NULL;
	len = 0;
	if ((parenth = ft_strsub(ret, ptr - ret + 2, get_content_size(ptr))))
	{
		if (*parenth == '#')
			len = 1;
		value = ft_get_param_value(sh, &parenth[len]);
		ft_strdel(&parenth);
		if (len == 1)
			value = ft_get_len(value);
	}
	return (ft_exp_end(ret, ptr, value, parenth));
}
