/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instrction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:20:35 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:20:36 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <21sh.h>

//optimiser : enlever les allocations d'environnement à chaques appels
t_word *o_get_input(int type)
{
	char **env;
	t_word *ret;
	char *input;

	if (type == 1)
		ft_putstr("\033[00;31mcmdand\033[00m >\n");
	else if (type == 2)
		ft_putstr("\033[00;31mcmdor\033[00m >\n");
	else if (type == 4)
		ft_putstr("\033[00;31mpipe\033[00m >\n");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	input = get_input(env);
	ret = eval_line(input);
	ft_freestrarr(env);
	return (ret);
}

char *backslash_get_input(void)
{
	char *ret;
	char **env;

	ft_putstr("\033[00;31mbackslash>\n\033[00m");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	ret = get_input(env);
	ft_freestrarr(env);
	return (ret);
}

char *q_get_input(char c)
{
	char **env;
	char *ret;
	char *ptr;

	if (c == '"')
		ft_putstr("\033[00;31md");
	ft_putstr("\033[00;31mquote>\n\033[00m");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	ret = get_input(env);
	if ((!(ptr = ft_strchr(ret, c)) || *(ptr - 1) == '\\' ))
		ret = ft_strjoin_fr(ft_stradd_char(ret, '\n'),  q_get_input(c));
	ft_freestrarr(env);
	return (ret);
}

char *heredoc_get_input(char *eoi)
{
	char **env;
	char *ret;

	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	ret = get_input(env);
	if (!ft_strequ(ret, eoi))
		ret = ft_strjoin_fr(ft_stradd_char(ret, '\n'),  heredoc_get_input(eoi));
	ft_freestrarr(env);
	return (ret);
}

