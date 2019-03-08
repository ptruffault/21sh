/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:10:38 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 16:10:39 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

t_process	*get_last_done_process(t_process *p)
{
	while (p)
	{
		if (p && p->status == DONE)
			return (p);
		p = p->next;
	}
	return (NULL);
}

char		*ft_exp_spec(char *ret, char *ptr, t_shell *sh)
{
	char		*val;
	t_process	*p;

	val = NULL;
	if ((ptr[1] == '!' || ptr[1] == '?') && sh->process
	&& (p = get_last_done_process(sh->process)))
		val = ft_itoa((ptr[1] == '!' ? p->pid : p->ret));
	else if (ptr[1] == '$')
		val = ft_itoa(sh->pid);
	ptr = ft_strpull(ret, ptr, 1, val);
	ft_strdel(&val);
	ft_strdel(&ret);
	return (ptr);
}

char		*ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = 0;
	while (ret && *ret && ret[i])
	{
		if ((ret && ret[i] == '~'
		&& !(ret = ft_exp_home_var(ret, &ret[i], sh->env)))
		|| (ret && ret[i] == '$' && ret[i + 1] == '{'
		&& !(ret = ft_exp_param(ret, sh, &ret[i])))
		|| (ret && ret[i] == '$' && ret[i + 1] && ft_strchr("$!?", ret[i + 1])
		&& !(ret = ft_exp_spec(ret, &ret[i], sh)))
		|| (ret && ret[i] == '$' && ret[i + 1] && !ft_strchr("$!?{", ret[i + 1])
		&& !(ret = ft_exp_envv_var(ret, &ret[i], sh))))
			return (NULL);
		i++;
	}
	return (ret);
}

t_word		*ft_expention(t_word *w)
{
	t_shell	*sh;
	t_word	*head;

	head = w;
	if (!(sh = ft_get_set_shell(NULL)))
		return (head);
	while (w)
	{
		if (IS_EXP(w->type) && w->word)
			if (!(w->word = ft_exp_var(w->word, sh)))
				return (head);
		w = w->next;
	}
	return (head);
}
