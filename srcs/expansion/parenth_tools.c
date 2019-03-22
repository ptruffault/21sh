/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenth_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:43:53 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

char	*ft_exp_end(char *ret, char *ptr, char *value, char *parenth)
{
	char *tmp;

	if (value && ft_isempty(value))
		ft_strdel(&value);
	if ((tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 2, value))
	&& ft_isempty(tmp))
		ft_strdel(&tmp);
	ft_strdel(&ret);
	ft_strdel(&value);
	ft_strdel(&parenth);
	return (tmp);
}

char	*ft_get_len(char *value)
{
	char *tmp;

	tmp = ft_itoa(ft_strlen(value));
	ft_strdel(&value);
	return (tmp);
}
