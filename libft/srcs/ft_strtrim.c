/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:26:37 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/03 16:16:49 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_find_end(char const *s, int i, size_t *end)
{
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != '\n' && s[i] != ' ')
			*end = i;
		i++;
	}
	return (i);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	end;
	size_t	start;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	end = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	start = i;
	if (!s[i])
		return (ft_strnew(0));
	i = ft_find_end(s, i, &end);
	str = ft_strnew(end - start + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
