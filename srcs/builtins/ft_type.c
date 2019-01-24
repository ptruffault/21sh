/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:13:40 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:13:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>
#define OPTS_A(t) (t[0] == 1)
#define OPTS_T(t) (t[1] == 1)
#define OPTS_P(t) (t[2] == 1)
#define OPTS_BP(t) (t[3] == 1)

static t_word *init_opts(char opts[4], t_word *w)
{
	int i;

	opts[0] = 0;
	opts[1] = 0;
	opts[2] = 0;
	opts[3] = 0;
	while (w->word && *w->word == '-')
	{
		i = 1;
		while (w->word[i])
		{
			if (ft_strchr("atpP", w->word[i]))
			{
				opts[0] = (w->word[i] == 'a' ? 1 : opts[0]);
				opts[1] = (w->word[i] == 't' ? 1 : opts[1]);
				opts[2] = (w->word[i] == 'p' ? 1 : opts[2]);
				opts[3] = (w->word[i] == 'P' ? 1 : opts[3]);
			}
			else
				warning_c("bad option", w->word[i]);
			i++;
		}
		w = w->next;
	}
	return (w);
}

static int handle_opts(t_word *w, char opts[4], t_shell *sh)
{
	int ret;

	ret = 0;
	if (OPTS_BP(opts))
		return (putfile(w, sh->env, opts[1]));
	else if (OPTS_P(opts))
		return (putcmd(w, sh->env, opts[1]));
	else if (OPTS_A(opts))
	{
		ret = ret + putword(w, opts[1]);
	 	ret = ret + putalias(w, sh->alias, opts[1]);
	 	ret = ret + putbuiltin(w, opts[1]);
		ret = ret + putfile(w, sh->env, opts[1]);
		ret = ret + putcmd(w, sh->env, opts[1]);
		return (ret);
	}
	else if (!putword(w, opts[1]) && !putalias(w, sh->alias, opts[1]) && !putbuiltin(w, opts[1]) &&
	!putfile(w, sh->env, opts[1]) && !putcmd(w, sh->env, opts[1]))
		return (0);
	return (1);
} 


void ft_type(t_word *w)
{
	t_shell *sh;
	char opts[4];

	if (!w || !w->word)
		return ;
	w = init_opts(opts, w);
	sh = ft_get_set_shell(NULL);
	while (w)
	{
		if (handle_opts(w, opts, sh) == 0)
			warning("not found", w->word);
		w = w->next;
	}
}
