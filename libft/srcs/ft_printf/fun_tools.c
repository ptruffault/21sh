/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:44:53 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/04 17:44:55 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		test_flag(char *s, char c)
{
	char *ptr;

	if (!s)
		return (0);
	if ((ptr = ft_strchr(s, c)))
	{
		if (ptr[1] == c && (c == 'l' || c == 'h'))
			return (2);
		return (1);
	}
	else
		return (0);
}

char	*my_strjoin(char *s1, char *s2)
{
	if (!s1 && s2)
		return (s2);
	if (s1 && !s2)
		return (s1);
	return (ft_strjoin_fr(s1, s2));
}

char	*ft_strmap_i(char *s, int (*f)(int))
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strnew(ft_strlen(s));
	if (new == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(s[i]);
		i++;
	}
	ft_strdel(&s);
	return (new);
}

char	*ft_strndup_fr(char *str, int n)
{
	char *ret;

	if (str == NULL)
	{
		ft_strnew(1);
	}
	ret = ft_strndup(str, n);
	ft_strdel(&str);
	return (ret);
}

void	ft_putnchar(char c, int n)
{
	while (n-- > 0)
		ft_putchar(c);
}
