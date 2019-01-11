/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

static char *ft_get_varname(char *s)
{
	char *ptr;
	int i;

	i = 0;
	ptr = s + 1;
	while (ptr[i] && (ft_isalpha(ptr[i]) || ptr[i] == '_'))
		i++;
	return (ft_strsub(s, ptr - s , i));
}

static char *ft_exp_envv_var(char *ret, char *ptr, t_shell *sh)
{
	char *name;
	char *value;
	char *tmp;

	name = ft_get_varname(ptr);
	if (!(value = get_tenvv_val(sh->env, name)))
		value = get_tenvv_val(sh->intern, name);
	if ((tmp = ft_strpull(ret, ptr , ft_strlen(name) + 1, value)))
	{
		ft_strdel(&ret);
		ret = tmp;
	}
	ft_strdel(&name);
	return (ret);
}

static char *ft_exp_home_var(char *ret, char *ptr, t_envv *envv)
{
	char *tmp;

	if ((tmp = ft_strpull(ret, ptr, 1, 
		get_tenvv_val(envv, "HOME"))))
	{
		ft_strdel(&ret);
		return(tmp);
	}
	return (NULL);
}

char  *ft_exp_var(char *ret, t_shell *sh)
{
	char *ptr;
	
	while ((ptr = ft_strchr(ret, '~')))
		ret = ft_exp_home_var(ret, ptr, sh->env);
	while ((ptr = ft_strchr(ret, '$')))
		ret = ft_exp_envv_var(ret, ptr, sh);
	return (ret);
}