/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*get_input(void)
{
	char	*input;
	char	buf;
	int		i;

	if (!(input = ft_strnew(1)))
		return (NULL);
	i = 0;
	while ((read(0, &buf, 1)) && buf != '\n')
	{
		input[i++] = buf;
		input = ft_realloc(input, i, i + 1);
	}
	input[i] = '\0';
	return (input);
}


int		main(int argc, char **argv, char **envv)
{
	t_envv	*my_envv;
	char	**input;
	char	*s;
	int		i;

	if (!(my_envv = new_tenvv()))
		return (-1);
	my_envv = init_tenvv(my_envv, envv);
	while (1)
	{
		ft_disp(my_envv, argc, argv);
		s = get_input();
		input = ft_strsplit(s, ';');
		ft_strdel(&s);
		i = 0;
		while (input[i])
			my_envv = read_cmd(my_envv, input[i++], input);
		ft_freestrarr(input);
	}
	return (0);
}
