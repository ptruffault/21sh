/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:13:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

t_envv *ft_export(t_shell *sh, char **argv)
{
	t_envv *tmp;
	char *name;
	char *val;
	int i;

	i = -1;
	while (argv[++i])
	{
		if (ft_isequal(argv[i]))
		{
			name = get_name(argv[i]);
			val = get_value(argv[i]);
			sh->env = ft_new_envv(sh->env ,name, val);
			ft_strdel(&name);
			ft_strdel(&val);
		}
		else if ((tmp = get_tenvv(sh->intern, argv[i])))
			sh->env = ft_new_envv(sh->env, tmp->name, tmp->value);
	}
	return (sh->env);
}
