/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curly_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static char *sub_handle_modifier(char *parenth, char *ptr, t_shell *sh)
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
	else if (*ptr == '=' && !(val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : NULL))) && v2 && 
	(sh->env = ft_new_envv(sh->env, v1, v2)))
		val = ft_strdup(v2);
	ft_strdel(&v1);
	ft_strdel(&v2);
	return (val);
}

static char *sub_get_param_value(char *old_parenth, t_shell *sh)
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
	ptr = ft_strpull(old_parenth, old_parenth , get_content_size(old_parenth) + 2 , value);
	return (ptr);
}

static char *handle_modifier(char *parenth, char *ptr, t_shell *sh)
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
	if (*ptr == '=' && !(val = ft_strdup(get_tenvv_val(sh->env, val1))) && val2 && 
	(sh->env = ft_new_envv(sh->intern, val1, val2)))
		val = ft_strdup(val2);
	ft_strdel(&val1);
	ft_strdel(&val2);
	return (val);
}

static char *ft_get_param_value(t_shell *sh, char *parenth)
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

char *ft_exp_param(char *ret, t_shell *sh, char *ptr)
{	
	char *value;
	char *tmp;
	char *parenth;
	int len;

	value = NULL;
	len = 0;
	if ((parenth = ft_strsub(ret, ptr - ret + 2 ,  get_content_size(ptr))))
	{
		if (*parenth == '#')
		{
			tmp = ft_strdup(parenth + 1);
			ft_strdel(&parenth);
			len = 1;
			parenth = tmp;
		}
		while (ft_str_startwith(parenth , "${") && (tmp = sub_get_param_value(parenth , sh)))
		{
				ft_strdel(&parenth);
				parenth = tmp;
		}
		if ((value = ft_get_param_value(sh, parenth)))
			ft_strdel(&parenth);
		if (len == 1)
		{
			tmp = ft_itoa(ft_strlen(value));
			ft_strdel(&value);
			value = tmp;
		}
		tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 2, value);
		ft_strdel(&ret);
		ret = tmp;
		ft_strdel(&value);
	}
	return (ret);
}

