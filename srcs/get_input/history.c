/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:57:42 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/01 17:59:51 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_input.h"

void	update_input(t_edit *e, char *s)
{
	if (s == NULL)
		ft_delete_line(e);
	ft_strdel(&e->input);
	if (s != NULL)
		e->input = s;
	else if (s == NULL)
		e->input = ft_strnew(3);
	e->curr = ft_strlen(s);
}

char	**ft_tab_realloc(char **buff, size_t size)
{
	char	**ret;
	int		x;

	if (!(ret = malloc(size)))
		return (NULL);
	if (!buff)
		return (buff);
	x = -1;
	while (buff[++x])
	{
		ret[x] = ft_strdup(buff[x]);
		free(buff[x]);
	}
	ret[x] = NULL;
	free(buff);
	return (ret);
}

void	hist_move_up(t_edit *e)
{
	int		x;
	t_hist	*hist;

	hist = e->hist;
	ft_delete_line(e);
	if (!hist || !hist->s)
		return ;
	x = -1;
	e->pos_hist++;
	while (hist->s && hist->next && ++x < e->pos_hist)
		hist = hist->next;
	if (hist->s)
		update_input(e, ft_strdup(hist->s));
	else
		e->pos_hist--;
}

void	hist_move_do(t_edit *e)
{
	t_hist	*hist;
	int		x;

	x = 0;
	hist = e->hist;
	ft_delete_line(e);
	if (e->pos_hist > -1)
		e->pos_hist--;
	if (e->pos_hist > -1)
	{
		while (hist->s && hist->next && x < e->pos_hist)
		{
			hist = hist->next;
			++x;
		}
		if (hist->s)
			update_input(e, ft_strdup(hist->s));
	}
	else if (e->pos_hist == -1)
		update_input(e, NULL);
}
