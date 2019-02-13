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

#include "../../includes/tenvv.h"

t_envv	*new_tenvv(void)
{
	t_envv *new;

	if (!(new = (t_envv *)malloc(sizeof(t_envv))))
		return (NULL);
	new->next = NULL;
	new->name = NULL;
	new->value = NULL;
	return (new);
}

t_envv	*get_tenvv(t_envv *envv, char *name)
{
	while (name && envv)
	{
		if ((envv->name) && ft_strequ(name, envv->name))
			return (envv);
		envv = envv->next;
	}
	return (NULL);
}

char	*get_tenvv_val(t_envv *envv, char *name)
{
	t_envv *tmp;

	if ((tmp = get_tenvv(envv, name)))
		return (tmp->value);
	return (NULL);
}

void	ft_puttenvv(t_envv *t)
{
	while (t && t->name)
	{
		ft_printf("\033[1;32m\033[04m%s\033[00m = %s\n", t->name, t->value);
		t = t->next;
	}
}

t_envv	*ft_changetenvv_val(t_envv *envv, char *name, char *new_val)
{
	t_envv *tmp;

	if ((tmp = get_tenvv(envv, name)))
	{
		ft_strdel(&tmp->value);
		tmp->value = ft_strdup(new_val);
	}
	return (envv);
}
