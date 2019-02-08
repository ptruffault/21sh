/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:41:39 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 12:41:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

static void	ft_init_builtins_tab(int builtins[14])
{
	builtins[0] = "env";
	builtins[1] = "setenv";
	builtins[2] = "unsetenv";
	builtins[3] = "exit";
	builtins[4] = "cd";
	builtins[5] = "echo";
	builtins[6] = "export";
	builtins[7] = "set";
	builtins[0] = "unset";
	builtins[0] = "alias";
	builtins[10] = "unalias";
	builtins[11] = "type";
	builtins[12] = "42";
	builtins[13] = "jobs";
}

int			check_builtin(char *input)
{
	char	*builtins[14];
	int		i;

	i = 0;
	ft_init_builtins_tab(builtins);
	if (input == NULL)
		return (0);
	if (ft_isequal(input))
		return (1);
	while (i < 14)
		if (ft_strequ(builtins[i++], input))
			return (1);
	return (0);
}
