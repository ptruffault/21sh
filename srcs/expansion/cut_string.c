/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:05:53 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

char		*ft_get_secondvalue(char *src)
{
	char	*cpy;
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if ((cpy = ft_strdup(src)))
	{
		if (*src == '$')
			cpy = ft_exp_var(cpy, ft_get_set_shell(NULL));
		while (cpy && cpy[i] && !((cpy[i] == ':'
			&& cpy[i + 1] && ft_strchr("?=+-", cpy[i + 1]))
			|| (cpy[i] == '#' || cpy[i] == '%') || cpy[i] == '}'))
			i++;
		ret = ft_strndup(cpy, i);
		ft_strdel(&cpy);
	}
	return (ret);
}

static char	*ft_get_op(char *s, int *i)
{
	int	start;

	start = *i;
	while (s && s[*i] && s[*i] == s[start])
		*i = *i + 1;
	return (ft_strsub(s, start, *i - start));
}

char		*ft_cut_begin(char *val, char *pat)
{
	char	*new;

	if (val && pat && ft_str_startwith(val, pat))
	{
		new = ft_strdup(val + ft_strlen(pat));
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

char		*ft_cut_end(char *val, char *pat)
{
	char	*new;

	if (val && pat && ft_str_endwith(val, pat))
	{
		new = ft_strndup(val, ft_strlen(val) - ft_strlen(pat));
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

char		*ft_cut_string(char *parenth, char *val, int *curr)
{
	char	*pattern;
	char	*op;

	if ((op = ft_get_op(parenth, curr)))
	{
		if (parenth[*curr] && parenth[*curr] != '}'
		&& (pattern = ft_get_secondvalue(&parenth[*curr])))
		{
			*curr = *curr + ft_strlen(pattern) - 1;
			if (ft_strequ(op, "##"))
				while (val && ft_str_startwith(val, pattern))
					val = ft_cut_begin(val, pattern);
			else if (ft_strequ(op, "%%"))
				while (val && ft_str_endwith(val, pattern))
					val = ft_cut_end(val, pattern);
			else if (*op == '#')
				val = ft_cut_begin(val, pattern);
			else if (*op == '%')
				val = ft_cut_end(val, pattern);
			ft_strdel(&pattern);
		}
		ft_strdel(&op);
	}
	return (val);
}
