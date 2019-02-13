#include "../../includes/shell42.h"

char *ft_get_secondvalue(char *src)
{
	int i;

	i = 0;
	while (src && src[i] && !((src[i] == ':' && src[i + 1] && ft_strchr("?=+-", src[i + 1]))
	|| (src[i] == '#' || src[i] == '%')))
		i++;
	return (ft_strndup(src, i));
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

int 	ft_str_endwith(char *s1, char *s2)
{
	int i;
	int j;

	if (s1 && s2)
	{
		j = 0;
		i = (int)ft_strlen(s1) - (int)ft_strlen(s2);
		while (i > 0 && s1[i] && s2[j])
		{
			if (s1[i++] != s2[j++])
				return (0);
		}
		if (s1[i] == 0 && s2[j] == 0)
			return (1);
	}
	return (0);
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
