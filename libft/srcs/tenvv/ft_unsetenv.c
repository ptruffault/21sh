/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:35:56 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:35:56 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tenvv.h>

t_envv		*ft_del_envv(t_envv *envv, char *name)
{
	t_envv *tmp;
	t_envv *prev;

	tmp = envv->next;
	prev = envv;
	if (ft_strequ(envv->name, name))
	{
		tmp = envv->next;
		envv = del_tenvv(envv);
		return (tmp);
	}
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			prev->next = tmp->next;
			tmp = del_tenvv(tmp);
			return (envv);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (envv);
}

t_envv		*ft_unsetenv(t_envv *envv, char **t)
{
	int i;

	i = 0;
	if (!envv)
		return (NULL);
	if (ft_strequ(*t, "-all"))
		return (ft_free_tenvv(envv));
	while (t[i])
		envv = ft_del_envv(envv, t[i++]);
	return (envv);
}
