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


int ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
		c == ' ')
		return (1);
	else
		return (0);
}

char	*ft_strndup(char *src, int len)
{
	char	*new;
	int		i;

	if (!(new = malloc(sizeof(char *) * len + 1)))
		return (NULL);
	i = 0;
	while (i < len && src[i] != '\0')
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}


static char *analyse(char *src)
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
			eval[i++] = 'Q';
			while (src[i] && src[i] != src[save])
				eval[i++] = 'q';
			if (src[i] == src[save])
				eval[i] = 'Q';
			else
			{
				error("invalid quotes", &src[save]);
			}
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

static t_word *new_tword(void)
{
	t_word *n;

	if (!(n = (t_word *)malloc(sizeof(t_word))))
		return (NULL);
	n->word = NULL;
	n->type = undef;
	n->next = NULL;
	return (n);
}

static t_word *get_next_word(t_word *w, char *eval, char *input, int *i, int *pos)
{
	char c;
	int begin;

	while (eval[*i] == ' ')
		*i = *i + 1;;
	if (eval[*i] == 0)
		return (w);
	if (eval[*i] == 'Q')
		*i = *i + 1;	
	c = eval[*i];
	begin = *i;
	while (eval[*i] && eval[*i] == c)
		*i = *i + 1;
	 if (!(w->word = ft_strndup(input + begin, *i - begin)))
	 	return (w);
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
	if (!(head = new_tword()) || !(head = get_next_word(head, eval, input, &i, &pos))
	|| eval[i] == 0)
		return (head);
	ft_putendl(eval);
	len = ft_strlen(input);
	tmp = head;
	while (i < len)
	{
		while (eval[i] == ' ')
			i++;
		if (eval[i] == 0)
			return (head);
		if (!(tmp->next = new_tword()))
			return (head);
		tmp = tmp->next;
		if (!(tmp = get_next_word(tmp, eval, input, &i, &pos)))
			return (head);
	}
	return (head);
}


void ft_free_tword(t_word *w)
{
	t_word *tmp;

	while (w)
	{
		printf("free tword %s\n",w->word );
		ft_strdel(&w->word);
		tmp = w->next;
		free(w);
		w = tmp;
	}
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
	ft_putwords(head);
	return (head);
}