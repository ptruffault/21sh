/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 14:49:50 by ptruffau          #+#    #+#             */
/*   Updated: 2018/06/21 14:50:01 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_get_next_word(char *str)
{
	char	*word;
	int		j;

	j = 0;
	word = NULL;
	while (ft_isspace(*str))
		str++;
	while (!(ft_isspace(str[j])) && str[j] != '\0')
		j++;
	if (!(word = ft_strnew(j)))
	{
		error("allocation failed", "ft_get_next_word");
		return (NULL);
	}
	word = ft_strncpy(word, str, j);
	return (word);
}
