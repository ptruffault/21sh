/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instrcution_parseur.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:22:05 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:22:06 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char **ft_get_file_content(char *path)
{
	int fd;
	char **ret;

	ret = NULL;
	if (!path)
	{
		warning ("file or needed as argument", "< [file] ");
		return (NULL);
	}
	if ((fd = ft_open(path)) > 0)
	{
		ret = ft_get_txt(fd);
		close(fd);
	}
	return (ret);
}

char **my_get_input(t_envv *e, char *s)
{
	char **ret;
	char **env;
	int i;

	if (!s)
	{
		warning ("End of instruction string needed as argument", "<< \"EOI\" ");
		return (NULL);
	}
	if (!(ret = (char **)malloc(sizeof(char *))))
		return (NULL);
	i = 0;
	env = tenvv_to_tab(e);
	while (42)
	{
		if (!(ret[i] = get_input(env)) || ft_strequ(ret[i], s))
		{
			ft_freestrarr(env);
			ret[i] = NULL;
			return (ret);
		}
		i++;
		ret = ft_realloc(ret, i , i + 1);
	}
	return (NULL);
}

