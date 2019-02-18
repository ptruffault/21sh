/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:24:19 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/18 15:25:49 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

static char		*ft_get_varname(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = s + 1;
	while (ptr[i] && (ft_isalpha(ptr[i]) || ptr[i] == '_'))
		i++;
	return (ft_strsub(s, ptr - s, i));
}

char			*ft_exp_envv_var(char *ret, char *ptr, t_shell *sh)
{
	char	*name;
	char	*value;
	char	*tmp;

	name = ft_get_varname(ptr);
	if (!(value = get_tenvv_val(sh->env, name)))
		value = get_tenvv_val(sh->intern, name);
	tmp = ft_strpull(ret, ptr, ft_strlen(name), value);
	ft_strdel(&ret);
	ft_strdel(&name);
	return (tmp);
}

char			*ft_exp_home_var(char *ret, char *ptr, t_envv *envv)
{
	char	*tmp;
	char	*val;

	if (!(val = get_tenvv_val(envv, "HOME")))
		ft_strdel(&ret);
	else if ((tmp = ft_strpull(ret, ptr, 0, val)))
	{
		ft_strdel(&ret);
		return (tmp);
	}
	return (NULL);
}
