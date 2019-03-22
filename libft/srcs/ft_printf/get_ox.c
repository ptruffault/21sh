/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:31:35 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/04 16:31:36 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*get_ox(t_param *p, char *tmp_val)
{
	char *ret;

	ret = NULL;
	if ((p->spec != 'o' && p->spec != 'x' && p->spec != 'O' && p->spec != 'X'
	&& p->spec != 'p'))
		return (NULL);
	if (p->spec == 'p')
		ret = ft_strdup("0x");
	if (ft_atoi(tmp_val) != 0)
	{
		if ((p->spec == 'x' && !(ret = ft_strdup("0x\0")))
		|| (p->spec == 'X' && !(ret = ft_strdup("0X\0")))
		|| ((p->spec == 'o' || p->spec == 'O') && !(ret = ft_strdup("0\0"))))
			return (NULL);
	}
	p->var_len = p->var_len + ft_strlen(ret);
	return (ret);
}
