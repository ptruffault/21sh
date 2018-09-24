/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:10:52 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:10:54 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

t_envv		*ft_unsetenv(t_envv *envv, char *name)
{
	t_envv *tmp;
	t_envv *prev;

	tmp = envv->next;
	prev = envv;
	if (ft_strequ(envv->name, name))
	{
		tmp = envv->next;
		del_tenvv(envv);
		return (tmp);
	}
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			prev->next = tmp->next;
			del_tenvv(tmp);
			return (envv);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	warning("there is no such var name in env", name);
	return (envv);
}

t_envv		*ft_setenv(t_envv *envv, char *name, char *value)
{
	t_envv *new;
	t_envv *tmp;

	if ((tmp = get_tenvv(envv, name)))
		return (ft_changetenvv_val(envv, name, value));
	if (!(new = new_tenvv())
	|| !(new->name = ft_strdup(name))
	|| !(new->value = ft_strdup(value)))
	{
		del_tenvv(new);
		return (envv);
	}
	new->next = envv;
	return (new);
}

void		ft_echo(char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		ft_putstr(input[i++]);
		ft_putchar('\t');
	}
	ft_putchar('\n');
}
