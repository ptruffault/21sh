/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 13:07:08 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/05 13:23:27 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
		c == ' ')
		return (1);
	else
		return (0);
}
