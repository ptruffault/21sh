/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenth_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:43:53 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/18 15:43:54 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

char	*ft_exp_end(char *ret, char *ptr, char *value, char *parenth)
{
	char *tmp;

	tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 2, value);
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
