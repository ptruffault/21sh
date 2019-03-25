/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:28:58 by ptruffau          #+#    #+#             */
/*   Updated: 2017/12/03 16:15:49 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		ft_free_tab(char **tab, int w)
{
	int i;

	i = 0;
	while (i < w)
	{
		ft_strdel(&tab[w]);
		w--;
	}
	ft_strdel(&*tab);
}

static void		ft_fill_tab(char *s, char c, char **tab, int l)
{
	int t;
	int i;
	int j;

	t = 0;
	i = 0;
	j = 0;
	while (t < l)
	{
		s = s + i + j;
		i = 0;
		j = 0;
		while (s[j + i] == c)
			j++;
		while (s[i + j] != '\0' && s[i + j] != c)
			i++;
		tab[t] = ft_strsub(s, j, i);
		if (tab[t] == NULL)
		{
			ft_free_tab(tab, t - 1);
			break ;
		}
		t++;
	}
}

static int		ft_count_words_by(char *s, char c)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (s[j] == c)
		j++;
	while (s[i + j] != '\0')
	{
		if (s[i + j] == c)
		{
			count += ft_count_words_by(s + i + j, c);
			break ;
		}
		i++;
	}
	if (s[i + j] != '\0' || (s[i + j - 1] != c && s[i + j - 1] != 0))
		count++;
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	int			length;

	tab = 0;
	if (s == NULL)
		return (NULL);
	length = ft_count_words_by((char*)s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (length + 1))))
		return (NULL);
	if (length == 0)
	{
		tab[0] = 0;
		return (tab);
	}
	ft_fill_tab((char*)s, c, tab, length);
	if (tab != NULL)
		tab[length] = 0;
	return (tab);
}
