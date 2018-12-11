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

void ft_putwords(t_word *w)
{
	while (w)
	{
		if (w->word)
			printf("PUTWORD:%s type = %i\n", w->word, w->type);
		w = w->next;
	}
}

char  *ft_delchar_n(char *s, int n)
{
	int len;

	if (n < 0 || (len = ft_strlen(s)) == 0 || n > len)
		return (NULL);
	while (n  < len)
	{
		s[n] = s[n + 1];
		n++;
	}
	return (s);
}



static char *analyse(char *src)
{
	char *eval;
	int len;
	int j;
	int i;

	i = -1;
	len = ft_strlen(src);
	if (!(eval = ft_strnew(len + 1)))
		return (NULL);
	while (src[++i])
	{
		if (src[i] == '\\')
		{
			if (src[i + 1])
			{
				src = ft_delchar_n(src, i);
				ft_putendl(src);
				eval[i++] = 'e';
			}
			else
			{
				error("\\ missing input", NULL); 
				break ;
			}
		}
		else if (ft_isspace(src[i]))
			eval[i] = ' ';
		else if (src[i] == '<')
			eval[i] = 'r';
		else if (src[i] == '>')
		{
			j = i;
			while (j > 0 && ft_isdigit(src[j - 1]))
				eval[--j] = 'r';
			eval[i] = 'r';
			if (i + 2 < len && src[i + 1] == '&')
			{
				eval[++i] = 'r';
				if (src[i + 1] == '-')
					eval[++i] = 'r';
				else
				{
					while (ft_isdigit(src[i + 1]))
						eval[++i] = 'r';
				}
			}
		}
		else if (src[i] == '&' || src[i] == '|' || src[i] == ';')
			eval[i] = 'o';
		else if (src[i] == '\'' || src[i] == '"')
		{
			int save;

			save = i;
			eval[i++] = ' ';
			while (src[i] && src[i] != src[save])
				eval[i++] = 'q';
			if (src[i] != src[save])
				error("HERE WE ADD INPUT", NULL);
		}
		else
			eval[i] = 'e';
	}
	eval[i] = 0;
	return (eval);
}

static t_word *find_type(t_word *w, char c, int *pos)
{
	if (c == 'o')
	{
		if (ft_strequ(w->word, "&&"))
			w->type = O_AND;
		else if (ft_strequ(w->word, "||"))
			w->type = O_OR;
		else if (ft_strequ(w->word, ";"))
			w->type = O_SEP;
		else if (ft_strequ(w->word, "|"))
			w->type = O_PIPE;
		else
			w->type = 0;
		*pos = 0;
	}
	else if (c == 'r')
	{
		char *ptr;

		if ((ptr = ft_strchr(w->word, '>')))
			w->type = (*(ptr + 1) == '>'? R_DRIGHT : R_RIGHT);
		else if ((ptr = ft_strchr(w->word, '<')))
			w->type = (*(ptr + 1) == '<'? R_DLEFT : R_LEFT);
		else
			w->type = 0;
	}
	else if (c == 'e')
	{
		if (*pos == 0)
			w->type = CMD;
		else
			w->type = PATH;
		*pos = *pos + 1;
	}
	else if (c == 'q')
		w->type = QUOTE;
	return (w);
}


static t_word *get_next_word(t_word *w, char *eval, char *input, int *i, int *pos)
{
	char c;
	int begin;

	c = eval[*i];
	begin = *i;
	while (eval[*i] && eval[*i] == c)
		*i = *i + 1;
	 if (!(w->word = ft_strndup(input + begin, *i - begin)))
	 	return (w);
	 w->position = *pos;
	 return (find_type(w, c, pos));
}

static t_word *ft_get_words(char *input, char *eval)
{
	t_word *head;
	t_word *tmp;
	int pos;
	int i;
	int len;

	i = 0;
	pos = 0;
	if (!(head = new_tword()))
		return (head);
	len = ft_strlen(input);
	tmp = head;
	while (eval[i] == ' ')
		i++;
	while (i < len)
	{
		if (eval[i] == 0 || !(tmp = get_next_word(tmp, eval, input, &i, &pos)))
			return (head);
		if (eval[i] == 0 || !(tmp->next = new_tword()))
			return (head);
		tmp = tmp->next;
		while (eval[i] == ' ')
			i++;
	}
	return (head);
}


// lis input et renvoie une liste chainée t_word avec chaque mot et son type
/*
	 O_AND = 1,
      O_OR = 2,
      O_SEP = 3, 
      O_PIPE = 4,
      R_LEFT = 5,
      R_RIGHT = 6,
      R_DLEFT = 7,
      R_DRIGHT = 8,
      CMD = 9, 
      QUOTE = 10,
      PATH = 11  
*/

t_word *eval_line(char *input)
{
	t_word *head;
	char *eval;

	if (!input|| !*input|| !(eval = analyse(input)))
		return (NULL);
	ft_putendl(eval);
	head = ft_get_words(input, eval);
	ft_strdel(&eval);
	return (head);
}