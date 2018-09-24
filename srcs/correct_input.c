/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:19 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:20 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static char	*ft_correct_one(t_envv *envv, char *s, char *ptr)
{
	char *ret;
	char *val;
	char *var_name;

	ret = NULL;
	if ((var_name = ft_get_next_word(ptr + 1))
	&& (val = ft_strdup(get_tenvv_val(envv, var_name))))
	{
		ret = ft_strpull(s, ptr, ft_strlen(var_name), val);
		ft_strdel(&s);
	}
	ft_strdel(&val);
	ft_strdel(&var_name);
	return (ret);
}

char		**ft_correct(char **input, t_envv *envv)
{
	int		i;
	char	*ptr;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		if ((ptr = ft_strchr(input[i], '$')) && !IS_SPACE(*(ptr + 1))
		&& (ptr - input[i] == 0 || IS_SPACE(*(ptr - 1))))
		{
			if (!(tmp = ft_correct_one(envv, input[i], ptr)))
				i++;
			else
				input[i] = tmp;
		}
		else if ((ptr = ft_strchr(input[i], '~')))
		{
			tmp = ft_strpull(input[i], ptr, 0, get_tenvv_val(envv, "HOME"));
			ft_strdel(&input[i]);
			input[i] = tmp;
		}
		else
			i++;
	}
	return (input);
}
