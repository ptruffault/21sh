/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char analyse(char c)
{
	if (ft_isspace(c))
		return(' ');
	if (ft_isdigit(c))
		return ('n');
	if (c == '<' || c == '>')
		return ('s');
	if (c == '&' || c == '|' || c == ';')
		return ('o');
	else
		return ('e');
}

char *get_token(char *s)
{
	int i;
	char *new;

	i = 0;
	if (!s || !*s || !(new = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		new[i] = analyse(s[i]);
		i++;
	}

	ft_putendl(new);
	ft_strdel(&new);
	return (new);
}