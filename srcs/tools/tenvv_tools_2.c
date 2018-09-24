/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:52 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:54 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

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

t_envv	*init_tenvv(t_envv *envv, char **tab_envv)
{
	int		i;
	int		len;
	t_envv	*tmp;

	i = 0;
	tmp = envv;
	len = ft_strarrlen(tab_envv);
	while (i < len)
	{
		if (!(tmp->name = get_name(tab_envv[i]))
		|| !(tmp->value = get_value(tab_envv[i])))
			return (envv);
		i++;
		if (!(tmp->next = new_tenvv()))
			return (envv);
		tmp = tmp->next;
	}
	envv = ft_setenv(envv, "USER", USER);
	envv = ft_setenv(envv, "HOME", HOME);
	return (envv);
}

t_envv	*ft_tenvv_cpy(t_envv *src)
{
	t_envv *tmp;
	t_envv *ret;

	if (!(ret = new_tenvv()))
		return (NULL);
	tmp = ret;
	while (src && src->name)
	{
		if (!(tmp->name = ft_strdup(src->name)) ||
		!(tmp->value = ft_strdup(src->value)))
			return (ret);
		src = src->next;
		if (src)
		{
			tmp->next = new_tenvv();
			tmp = tmp->next;
		}
	}
	return (ret);
}

void	del_tenvv(t_envv *envv)
{
	if (!envv)
		return ;
	ft_strdel(&envv->name);
	ft_strdel(&envv->value);
	envv->next = NULL;
	free(envv);
	envv = NULL;
}

void	ft_free_tenvv(t_envv *envv)
{
	t_envv *tmp;

	while (envv)
	{
		tmp = envv;
		envv = envv->next;
		del_tenvv(tmp);
	}
}
