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
#include <parseur.h>

t_word *o_get_input(int type)
{
	if (type == O_AND)
		ft_putstr("\033[00;31mcmdand\033[00m\n>");
	else if (type == O_OR)
		ft_putstr("\033[00;31mcmdor\033[00m\n>");
	else if (type == O_PIPE)
		ft_putstr("\033[00;31mpipe\033[00m\n>");
	return (eval_line(get_input()));
}

char *backslash_get_input(void)
{
	ft_putstr("\033[00;31mbackslash>\n\033[00m");
	return (get_input());
}

char *p_get_input(char c)
{
	char s;
	char *ret;
	char *ptr;

	s = (c == '(' ? ')' : (c == '{' ? '}' : (c == '[' ? ']' : 'R')));
	ft_printf("\033[00;31md '%c' expect '%s' >\033[00m\n");
	ret = get_input();
	if ((!(ptr = ft_strchr(ret, s)) || *(ptr - 1) == '\\' ))
		ret = ft_strjoin_fr(ret,  p_get_input(c));
	return (ret);
}


char *q_get_input(char c)
{
	char *ret;
	char *ptr;

	if (c == '"')
		ft_putstr("\033[00;31mdquote>\033[00m\n");
	else if (c == '\'')
		ft_putstr("\033[00;31mquote>\033[00m\n");
	ret = get_input();
	if ((!(ptr = ft_strchr(ret, c)) || *(ptr - 1) == '\\' ))
		ret = ft_strjoin_fr(ft_stradd_char(ret, '\n'),  q_get_input(c));
	return (ret);
}

char *heredoc_get_input(char *eoi)
{
	char *ret;

	ft_putstr("\033[00;34mheredoc>\n\033[00m");
	ret = get_input();
	if (!ft_strequ(ret, eoi))
		return (ft_strjoin_fr(ft_stradd_char(ret, '\n'),  heredoc_get_input(eoi)));
	else
		return (NULL);
}

