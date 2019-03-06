/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:02:47 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell42.h"

int			ft_twordlen(t_word *w)
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

t_redirect	*parse_heredoc(t_redirect *new, t_word *w)
{
	if (w->next && w->next->word)
	{
		new->path = ft_strdup(w->next->word);
		new->heredoc = heredoc_get_input(new->path);
		return (new);
	}
	ft_free_redirection(new);
	return (NULL);
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
		if (w->word && !ft_isempty(w->word) && (arr[i] = ft_strdup(w->word)))
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
