/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:21:10 by ptruffau          #+#    #+#             */
/*   Updated: 2019/03/22 16:23:35 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

int			ft_add_char(char buf, t_edit *e)
{
	size_t	i;
	size_t	size;

	if (e->select != -1)
		delete_left(e);
	if (!ft_isprint(buf) || !e->hist->s)
		return (SUCCESS);
	i = (int)ft_strlen(e->hist->s);
	size = i + 1;
	while (i > 1 && i > e->curr)
	{
		e->hist->s[i] = e->hist->s[i - 1];
		i--;
	}
	e->hist->s[e->curr] = buf;
	if (!(e->hist->s = ft_realloc(e->hist->s, size, size + 1)))
		return (FAILURE);
	e->hist->s[size] = '\0';
	e->curr++;
	if (e->select != -1)
		e->select = -1;
	return (SUCCESS);
}

static int	delete_simple_left(t_edit *e)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (e->curr < 1)
		return (SUCCESS);
	i = 0;
	j = 0;
	if (!(tmp = ft_strnew(ft_strlen(e->hist->s) - 1)))
		return (FAILURE);
	while (e->hist->s[j])
	{
		if (j != e->curr - 1)
			tmp[i++] = e->hist->s[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	curr_move_left(e);
	return (SUCCESS);
}

static int	delete_multiple_left(t_edit *e, int stop)
{
	char	*tmp;
	size_t	i;
	size_t	x;
	size_t	size;

	i = 0;
	i = (e->curr > e->select_pos ? e->curr : e->select_pos);
	if (!(tmp = ft_strnew(ft_strlen(e->hist->s) - (i - stop))))
		return (FAILURE);
	ft_strncpy(tmp, e->hist->s, stop);
	x = stop;
	while (e->hist->s[i++])
		tmp[x++] = e->hist->s[i];
	tmp[x] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	e->curr = e->curr > e->select_pos ? e->select_pos : e->curr;
	if (e->curr > (size = ft_strlen(e->hist->s)))
		e->curr = size;
	return (SUCCESS);
}

void		delete_left(t_edit *e)
{
	size_t	stop;

	if (e->select == -1)
		delete_simple_left(e);
	else
	{
		stop = e->curr > e->select_pos ? e->select_pos : e->curr;
		delete_multiple_left(e, stop);
	}
	e->select = -1;
}

void		delete_on(t_edit *e)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*tmp;

	e->select = -1;
	if (e->curr == (size = ft_strlen(e->hist->s)))
		return ;
	i = 0;
	j = 0;
	if (!(tmp = ft_strnew(size - 1)))
		return ;
	while (e->hist->s[j])
	{
		if (j != e->curr)
			tmp[i++] = e->hist->s[j];
		j++;
	}
	tmp[i] = '\0';
	ft_strdel(&e->hist->s);
	e->hist->s = tmp;
	return ;
}
