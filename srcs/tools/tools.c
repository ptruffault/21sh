/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:12:02 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:12:03 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char	*get_equal(char *name, char *value)
{
	char *tmp;
	char *ret;

	if (!(tmp = ft_strnew(ft_strlen(name) + 2)))
		return (NULL);
	tmp = ft_strcpy(tmp, name);
	tmp[ft_strlen(name)] = '=';
	tmp[ft_strlen(name) + 1] = '\0';
	if (!(ret = ft_strjoin(tmp, value)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (ret);
}

char	*get_name(char *equal)
{
	int		i;
	char	*name;

	i = 0;
	while (equal[i] != '=')
	{
		if (equal[i++] == '\0')
			return (NULL);
	}
	if (!(name = ft_strnew(i)))
		return (NULL);
	name = ft_strncpy(name, equal, i);
	name[i + 1] = '\0';
	return (name);
}

char	*get_value(char *equal)
{
	char *ptr;
	char *value;

	if (!(ptr = ft_strchr(equal, '=') + 1)
		|| !(value = ft_strdup(ptr)))
		return (NULL);
	return (value);
}

char	*ft_get_input(void)
{
	char	*input;
	int		ret;
	char	buf;
	int		i;
	int		count;

	if (!(input = ft_strnew(1)))
		return (NULL);
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n')
	{
		input[i++] = buf;
		input = ft_realloc(input, count, count + 1);
		count++;
	}
	input[i] = '\0';
	if (!ret)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

int		check_void_input(char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (!IS_SPACE(s[i++]))
			return (0);
	return (1);
}
