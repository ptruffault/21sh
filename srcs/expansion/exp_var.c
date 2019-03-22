/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:36:54 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static char	*ft_get_varname(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = s + 1;
	while (ptr[i] && (ptr[i] == '_' || ft_isalpha(ptr[i])
	|| ft_isdigit(ptr[i]) || ptr[i] == '~' || ptr[i] == '@'))
		i++;
	return (ft_strsub(s, ptr - s, i));
}

char		*ft_exp_envv_var(char *ret, char *ptr, t_shell *sh)
{
	char	*name;
	char	*value;
	char	*tmp;

	name = NULL;
	value = NULL;
	if ((name = ft_get_varname(ptr))
	&& !(value = get_tenvv_val(sh->env, name))
	&& !(value = get_tenvv_val(sh->intern, name)))
		ft_strdel(&ret);
	else if ((tmp = ft_strpull(ret, ptr, ft_strlen(name), value)))
	{
		ft_strdel(&ret);
		ret = tmp;
	}
	ft_strdel(&name);
	return (ret);
}

char		*ft_exp_home_var(char *ret, char *ptr, t_envv *envv)
{
	char	*tmp;
	char	*val;

	tmp = NULL;
	if ((val = get_tenvv_val(envv, "HOME"))
	&& (tmp = ft_strpull(ret, ptr, 0, val)))
	{
		ft_strdel(&ret);
		return (tmp);
	}
	ft_strdel(&ret);
	return (NULL);
}
