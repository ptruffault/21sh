/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespace.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:42:44 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/08 15:52:02 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		**ft_strsplit_whitespace(char *str)
{
	int		i;
	int		k;
	char	**t;

	i = 0;
	k = 0;
	t = NULL;
	if (!(t = (char **)malloc(sizeof(char *) * ft_count_word(str) + 1)))
	{
		error("allocation failed", "ft_strsplit_whitespace");
		return (NULL);
	}
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\0')
		{
			t[k] = ft_get_next_word(&str[i]);
			i = i + ft_strlen(t[k++]);
		}
	}
	t[k] = NULL;
	return (t);
}
