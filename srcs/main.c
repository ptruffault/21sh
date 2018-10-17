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

char *ft_straddchar_at(char *str, char c, int pos)
{
	int i;
	int len;

	if (!str)
		return (ft_char_to_str(c));
	if (pos > (int)ft_strlen(str) || pos < 0)
		return (str);
	len  = ft_strlen(str);
	i = len + 1;
	while (i > pos)
	{
		str[i] = str[i - 1];
		i--;	
	}
	str[pos] = c;
	str = ft_realloc(str, len + 1, len + 2);
	return (str);
}

char *correct_syntax(char *s)
{
	int i;
	int sa;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			sa = i;
			if (s[i] == '>' && i > 0 && ft_isdigit(s[i - 1]))
			{
				while (ft_isdigit(s[i - 1]))
					i--;
			}
			if (!IS_SPACE(s[i - 1]))
				s = ft_straddchar_at(s, ' ', i);
			i = sa + 1;
			while ((s[i] == s[sa] || 
			((s[sa] == '>' || s[sa] == '<') && (s[i] == '&' || ft_isdigit(s[i])))))
				i++;
			if (!IS_SPACE(s[i]))
				s = ft_straddchar_at(s, ' ', i);
		}
		i++;
	}
	return (s);
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
	while (42)
	{
		ft_disp(my_envv, argc, argv);
		s = correct_syntax(get_input(envv));
		input = ft_strsplit(s, ';');
		ft_strdel(&s);
		i = 0;
		while (input[i])
			my_envv = read_cmd(my_envv, input[i++], input);
		ft_freestrarr(input);
	}
	return (0);
}
