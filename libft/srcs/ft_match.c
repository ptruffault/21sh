/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:25:59 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:26:00 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_match(char *s1, char *s2)
{
	if (*s1 && *s2 == '*')
		return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
	else if (!(*s1) && *s2 == '*')
		return (ft_match(s1, s2 + 1));
	else if (*s1 && *s2 && *s1 == *s2)
		return (ft_match(s1 + 1, s2 + 1));
	else if (!(*s1) && !(*s2))
		return (1);
	return (0);
}
