/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:19:48 by ptruffau          #+#    #+#             */
/*   Updated: 2018/11/07 14:19:50 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char *analyse(char *src)
{
	char *eval;
	int len;
	int j;
	int i;

	i = -1;
	len = ft_strlen(src);
	if (!(eval = ft_strnew(len)))
		return (NULL);
	while (src[++i])
	{
		if (ft_isspace(src[i]))
			eval[i] = ' ';
		else if (src[i] == '<')
			eval[i] = 's';
		else if (src[i] == '>')
		{
			j = i;
			while (j > 0 && ft_isdigit(src[j - 1]))
				eval[--j] = 's';
			eval[i] = 's';
			if (i + 2 < len && src[i + 1] == '&')
			{
				eval[++i] = 's';
				if (src[i + 1] == '-')
					eval[++i] = 's';
				else
				{
					while (ft_isdigit(src[i + 1]))
						eval[++i] = 's';
				}
			}
		}
		else if (src[i] == '&' || src[i] == '|' || src[i] == ';')
			eval[i] = 'o';
		else
			eval[i] = 'e';
	}
	return (eval);
}

int ft_is_word(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ')
			return (1);
	return (0);
}

void ft_word_limit(char *eval, int i, int *begin, int *end)
{
	char c;

	c = eval[i];
	*begin = i;
	*end = i;
	while (eval[*end] == c)
		*end = *end + 1;
}

t_word *new_tword(void)
{
	t_word *n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

t_word *ft_get_words(char *input, char *eval)
{
	t_word *head;
	t_word *tmp;
	int i;
	int begin;
	int end;

	i = -1;
	if (!(head = new_tword()))
		return (NULL);
	tmp = head;
	while (eval[++i])
	{
		if (eval[i] == ' ')
			i++;
		else
		{
			ft_word_limit(eval, i, &begin, &end);
			tmp->word = ft_strndup(input + begin, end - begin);
			i = end;
			tmp->next = new_tword();
			tmp = tmp->next;
		}
	}
	return (head);
}

void ft_put_word(t_word *w)
{
	t_word *tmp;

	tmp = w;
	while (tmp)
	{
		printf("tmp->word %s\t", tmp->word);
		tmp = tmp->next;
	}
}

t_word *tokeniser(char *input)
{
	t_word *head;
	char *eval;

	if (!input|| !*input|| !(eval = analyse(input)))
		return (NULL);
	ft_putendl(eval);
	if (!(head = ft_get_words(input, eval)))
		return (NULL);
	ft_put_word(head);
	ft_strdel(&eval);
	return (head);
}