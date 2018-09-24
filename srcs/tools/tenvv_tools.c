/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:41 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:42 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

t_envv	*get_tenvv(t_envv *envv, char *name)
{
	t_envv *tmp;

	tmp = envv;
	while (tmp)
	{
		if ((tmp->name) && ft_strequ(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_tenvv_val(t_envv *envv, char *name)
{
	while (envv)
	{
		if (ft_strequ(name, envv->name))
			return (envv->value);
		envv = envv->next;
	}
	return (NULL);
}

void	ft_puttenvv(t_envv *envv)
{
	t_envv *tmp;

	tmp = envv;
	while (tmp != NULL && tmp->name != NULL && tmp->value != NULL)
	{
		ft_putstr("\033[1;32m\033[04m");
		ft_putstr(tmp->name);
		ft_putstr("\033[00m = ");
		ft_putstr(tmp->value);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

t_envv	*ft_changetenvv_val(t_envv *envv, char *name, char *new_val)
{
	t_envv *tmp;

	tmp = envv;
	if (!name)
		return (envv);
	if (!new_val)
		return (ft_unsetenv(envv, name));
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			ft_strdel(&tmp->value);
			tmp->value = ft_strdup(new_val);
			return (envv);
		}
		tmp = tmp->next;
	}
	error("no such envv var", name);
	return (envv);
}
