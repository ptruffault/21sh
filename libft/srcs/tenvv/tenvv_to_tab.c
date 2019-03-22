/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:42:31 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/05 13:45:47 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tenvv.h>

static char	*get_equal(char *name, char *value)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	if (!(tmp = ft_strjoin(name, "=")))
		return (NULL);
	ret = ft_strjoin(tmp, value);
	ft_strdel(&tmp);
	return (ret);
}

static int	envv_len(t_envv *envv)
{
	int		i;

	i = 0;
	while (envv)
	{
		i++;
		envv = envv->next;
	}
	return (i + 1);
}

char		**tenvv_to_tab(t_envv *envv)
{
	char	**t;
	int		i;

	i = 0;
	if (!envv || !(t = (char **)malloc(sizeof(char *) * envv_len(envv))))
		return (NULL);
	while (envv)
	{
		if ((t[i] = get_equal(envv->name, envv->value)))
			i++;
		envv = envv->next;
	}
	t[i] = NULL;
	if (i == 0)
	{
		free(t);
		return (NULL);
	}
	return (t);
}
