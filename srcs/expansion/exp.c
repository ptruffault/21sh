/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

char  *ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = 0;
	while (ret && ret[i])
	{
		if (ret && ret[i] == '~')
			ret = ft_exp_home_var(ret, &ret[i], sh->env);
		if ((ret && ret[i] == '$') && ret[i+ 1] == '{')
			ret = ft_exp_param(ret, sh, &ret[i]);
		if (ret && (ret[i] == '$') && ret[i + 1] != '{')
			ret = ft_exp_envv_var(ret, &ret[i], sh);
		i++;
	}
	return (ret);
}

t_word *ft_expention(t_word *w)
{
	t_shell *sh;
	t_word *tmp;

	if (!(sh = ft_get_set_shell(NULL)))
		return (NULL);
	tmp = w;
	while (tmp)
	{
		if (IS_CMD(tmp->type) && tmp->word)
			tmp->word = ft_exp_var(tmp->word, sh);
		tmp = tmp->next;
	}
	return (w);
}