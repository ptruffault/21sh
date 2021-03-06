/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/20 18:11:13 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell42.h>

static int	ft_twordlen(t_word *w)
{
	int	i;

	i = 0;
	while (w)
	{
		w = w->next;
		i++;
	}
	return (i);
}

void		ft_delete_char(t_eval *e)
{
	int i;
	int len;

	i = e->curr;
	len = ft_strlen(e->s);
	while (i < len && e->s[e->curr] && e->s[i + 1])
	{
		e->s[i] = e->s[i + 1];
		i++;
	}
	e->s[i] = '\0';
}

t_redirect	*parse_heredoc(t_redirect *ret, t_word *w)
{
	t_shell *sh;

	sh = ft_get_set_shell(NULL);
	if (w->next && w->next->word && w->next->type != OPERATEUR
	&& w->next->type != REDIRECT)
	{
		if (!(ret->path = ft_strdup(w->next->word)))
			return (ft_free_redirection(ret));
		sh->heredoc = 1;
		ret->heredoc = heredoc_get_input(ret->path, sh);
		sh->heredoc = 0;
		return (ret);
	}
	return (ft_free_redirection(ret));
}

char		ft_parse_back(char c)
{
	if (c == 'n')
		return ('\n');
	if (c == 't')
		return ('\t');
	if (c == 'a')
		return ('\a');
	if (c == 'f')
		return ('\f');
	if (c == 'r')
		return ('\r');
	if (c == 'v')
		return ('\v');
	return (c);
}

char		**ft_twordto_arr(t_word *w)
{
	char	**arr;
	int		i;

	i = 0;
	if (!w || !(w = ft_expention(w)))
		return (NULL);
	if (!(arr = malloc(sizeof(char *) * (ft_twordlen(w) + 1))))
		return (NULL);
	while (w)
	{
		if (w->word && (arr[i] = ft_strdup(w->word)))
			i++;
		w = w->next;
	}
	if (i == 0)
	{
		free(arr);
		return (NULL);
	}
	arr[i] = NULL;
	return (arr);
}
