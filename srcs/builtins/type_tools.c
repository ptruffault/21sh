/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:56:45 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

int	putword(t_word *w, int t)
{
	if (ft_strequ(w->word, ";") || ft_strequ(w->word, "&&")
		|| ft_strequ(w->word, "||") || ft_strequ(w->word, "||")
		|| ft_strequ(w->word, "|"))
	{
		if (t)
			ft_printf("keyword\n");
		else
			ft_printf("%s is a shell keyword\n", w->word);
		return (1);
	}
	return (0);
}

int	putfile(t_word *w, t_envv *env, int t)
{
	char *value;

	if ((value = absolute_path(w->word, env)))
	{
		if (t == 1)
			ft_printf("file\n");
		else
			ft_printf("%s is %s\n", w->word, value);
		ft_strdel(&value);
		return (1);
	}
	return (0);
}

int	putcmd(t_word *w, t_envv *env, int t)
{
	char *value;

	if ((value = search_in_envv(w->word, env)))
	{
		if (t == 1)
			ft_printf("command\n");
		else
			ft_printf("%s is %s\n", w->word, value);
		ft_strdel(&value);
		return (1);
	}
	return (0);
}

int	putbuiltin(t_word *w, int t)
{
	if (check_builtin(w->word))
	{
		if (t == 1)
			ft_printf("builtin\n");
		else
			ft_printf("%s is a shell builtins\n", w->word);
		return (1);
	}
	return (0);
}

int	putalias(t_word *w, t_envv *alias, int t)
{
	char *value;

	if ((value = get_tenvv_val(alias, w->word)))
	{
		if (t == 1)
			ft_printf("alias\n");
		else
			ft_printf("%s is an alias for %s\n", w->word, value);
		return (1);
	}
	return (0);
}
