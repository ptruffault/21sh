/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_sub_parenth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:57:04 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/08 13:30:16 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static char	*sub_handle_modifier(char *parenth, char *ptr, t_shell *sh)
{
	char *v1;
	char *v2;
	char *val;

	if (!(v1 = ft_strndup(parenth, ptr - parenth - 1)))
		return (NULL);
	v2 = ft_strdup(ptr + 1);
	val = NULL;
	if (*ptr == '-')
		val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : v2));
	else if (*ptr == '+')
		val = ft_strdup((get_tenvv(sh->env, v1) ? v2 : NULL));
	if (*ptr == '?' && !(val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : NULL))))
		error(v1, v2);
	else if (*ptr == '='
	&& !(val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : NULL))) && v2
	&& (sh->env = ft_new_envv(sh->env, v1, v2)))
		val = ft_strdup(v2);
	ft_strdel(&v1);
	ft_strdel(&v2);
	return (val);
}

static char	*sub_get_param_value(char *old_parenth, t_shell *sh)
{
	char *parenth;
	char *value;
	char *ptr;

	if (!(parenth = ft_strsub(old_parenth, 2, get_content_size(old_parenth))))
		return (NULL);
	value = NULL;
	if (ft_str_startwith(parenth, "${"))
		parenth = sub_get_param_value(parenth, sh);
	if ((ptr = ft_strchr(parenth, ':')) && ++ptr)
	{
		if (ft_strchr("-+?=", *ptr))
			value = sub_handle_modifier(parenth, ptr, sh);
		else
		{
			error_c("unrecognized modifier", *ptr);
			return (NULL);
		}
	}
	else
		value = ft_strdup(parenth);
	ft_strdel(&parenth);
	ptr = ft_strpull(old_parenth, old_parenth,
	get_content_size(old_parenth) + 3, value);
	return (ptr);
}

char		*ft_exp_param_sub(char *parenth, t_shell *sh)
{
	char *tmp;

	while (ft_str_startwith(parenth, "${")
	&& (tmp = sub_get_param_value(parenth, sh)))
	{
		ft_strdel(&parenth);
		parenth = tmp;
	}
	return (parenth);
}
