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

#include <21sh.h>

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
		if ((ptr = ft_strchr(input[i], '$')) && !ft_isspace(*(ptr + 1))
		&& (ptr - input[i] == 0 || ft_isspace(*(ptr - 1))))
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
