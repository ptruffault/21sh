#include "../../includes/shell42.h"

char *ft_get_secondvalue(char *src)
{
	char *cpy;
	int i;

	i = 0;
	cpy = ft_strdup(src);
	if (ft_str_startwith(cpy, "${"))
	{
		cpy = ft_exp_param(cpy, ft_get_set_shell(NULL), cpy);
	}
	while (cpy && cpy[i] && !((cpy[i] == ':' && cpy[i + 1] && ft_strchr("?=+-", cpy[i + 1]))
	|| (cpy[i] == '#' || cpy[i] == '%')))
		i++;
	return (ft_strndup(cpy, i));
}



static char *ft_get_op(char *s, int *i)
{
	int start;

	start = *i;
	while (s && s[*i] && s[*i] == s[start])
		*i = *i + 1;
	return (ft_strsub(s, start, *i - start));
}

char *ft_cut_begin(char *val, char *pat)
{
	char *new;

	if (val && pat && ft_str_startwith(val, pat))
	{
		new = ft_strdup(val + ft_strlen(pat));
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

char	*ft_cut_end(char *val, char *pat)
{
	char *new;

	if (val && pat && ft_str_endwith(val, pat))
	{
		new = ft_strndup(val , ft_strlen(val) - ft_strlen(pat));
		ft_strdel(&val);
		return (new);
	}
	return (val);
}

char		*ft_cut_string(char *parenth, char *val, int *curr)
{
	char *pattern;
	char *op;

	if ((op = ft_get_op(parenth, curr)))
	{
		if (parenth[*curr] &&  parenth[*curr] != '}'
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
