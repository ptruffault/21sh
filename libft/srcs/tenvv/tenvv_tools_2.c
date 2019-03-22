/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenvv_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:52 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 15:09:42 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tenvv.h>

t_envv	*ft_tenvv_cpy(t_envv *src)
{
	t_envv *tmp;
	t_envv *ret;

	if (!(ret = new_tenvv()))
		return (NULL);
	tmp = ret;
	while (src)
	{
		if (!(tmp->name = ft_strdup(src->name)) 
		|| !(tmp->value = ft_strdup(src->value)))
			return (ft_free_tenvv(ret));
		src = src->next;
		if (src)
		{
			tmp->next = new_tenvv();
			tmp = tmp->next;
		}
	}
	return (ret);
}

t_envv	*del_tenvv(t_envv *envv)
{
	if (envv)
	{
		ft_strdel(&envv->name);
		ft_strdel(&envv->value);
		envv->next = NULL;
		free(envv);
	}
	return (NULL);
}

t_envv	*ft_free_tenvv(t_envv *envv)
{
	t_envv *tmp;

	while (envv)
	{
		tmp = envv;
		envv = envv->next;
		tmp = del_tenvv(tmp);
	}
	return (NULL);
}
