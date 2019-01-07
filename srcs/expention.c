/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

char *ft_get_varname(char *s)
{
	char *ptr;
	int i;

	i = 0;
	ptr = s + 1;
	while (ptr[i] && (ft_isalpha(ptr[i]) || ptr[i] == '_'))
		i++;
	return (ft_strsub(s, ptr - s , i));
}

char  *ft_exp_var(char *ret)
{
	char *ptr;
	char *tmp;
	char *name;
	
	while ((ptr = ft_strchr(ret, '~')))
	{
		if ((tmp = ft_strpull(ret, ptr, 1, 
		get_tenvv_val(ft_get_set_envv(NULL), "HOME"))))
		{
			ft_strdel(&ret);
			ret = tmp;
		}
	}
	while ((ptr = ft_strchr(ret, '$')))
	{
		name = ft_get_varname(ptr);
		if ((tmp = ft_strpull(ret, ptr , ft_strlen(name) + 1, 
		get_tenvv_val(ft_get_set_envv(NULL), name))))
		{
			ft_strdel(&ret);
			ret = tmp;
		}
		ft_strdel(&name);
	}
	return (ret);
}

char *ft_expention(t_word *w)
{
	char *ret;

	ret = ft_strdup(w->word);
	if (w->type == VAR || w->type == QUOTE)
	{
		ret = ft_exp_var(ret);
	}
	return (ret);
}