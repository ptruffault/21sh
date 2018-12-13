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

#include <21sh.h>

# define IS_QUOTE(x) (x == '\'' || x == '"')

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

//optimiser les get_input en enleveant les allocation d'environnement a chaque appel

t_word *o_get_input(int type)
{
	char **env;
	t_word *ret;
	char *input;

	if (type == 1)
		ft_putstr("cmdand");
	else if (type == 2)
		ft_putstr("cmdor");
	else if (type == 4)
		ft_putstr("pipe");
	ft_putstr("> ");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	input = get_input(env);
	ret = eval_line(input);
	ft_freestrarr(env);
	return (ret);
}

char *q_get_input(char c)
{
	char **env;
	char *ret;
	char *ptr;

	if (c == '"')
		ft_putchar('d');
	ft_putstr("quote> ");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	ret = get_input(env);
	if ((!(ptr = ft_strchr(ret, c)) || *(ptr - 1) == '\\' ))
		ret = ft_strjoin_fr(ft_stradd_char(ret, '\n'),  q_get_input(c));
	ft_freestrarr(env);
	return (ret);
}

char *heredoc_get_input(char *eoi)
{
	char **env;
	char *ret;

	ft_putstr("heredoc> ");
	env = tenvv_to_tab(ft_get_set_envv(NULL));
	ret = get_input(env);
	if (!ft_strequ(ret, eoi))
		ret = ft_strjoin_fr(ft_stradd_char(ret, '\n'),  heredoc_get_input(eoi));
	ft_freestrarr(env);
	return (ret);
}



typedef struct 	s_eval
{
	char *s;
	char *eval;
}				t_eval;

t_eval  analyse(char *src)
{
	t_eval e;
	int len;
	int j;
	int i;

	i = -1;
	len = ft_strlen(src);
	if (!(e.eval = ft_strnew(len + 1)))
		return (e);
	while (src[++i])
	{
		if (src[i] == '\\')
		{
			if (src[i + 1])
			{
				src = ft_delchar_n(src, i);
				e.eval[i] = 'e';
			}
			else
			{
				error("\\ missing input", NULL); 
				break ;
			}
		}
		else if (ft_isspace(src[i]))
			e.eval[i] = ' ';
		else if (src[i] == '<')
			e.eval[i] = 'r';
		else if (src[i] == '>')
		{
			j = i;
			while (j > 0 && ft_isdigit(src[j - 1]))
				e.eval[--j] = 'r';
			e.eval[i] = 'r';
			if (i + 2 < len && src[i + 1] == '&')
			{
				e.eval[++i] = 'r';
				if (src[i + 1] == '-')
					e.eval[++i] = 'r';
				else
				{
					while (ft_isdigit(src[i + 1]))
						e.eval[++i] = 'r';
				}
			}
		}
		else if (src[i] == '&' || src[i] == '|' || src[i] == ';')
			e.eval[i] = 'o';
		else if (IS_QUOTE(src[i]))
		{
			int save;

			save = i;
			while ((src[i] != src[save] || i == save))
			{		
				e.eval[i++] = 'q';
				if (src[i] == 0)
				{
					src = ft_strjoin_fr(ft_stradd_char(src, '\n'), q_get_input(src[save]));
					e.eval = ft_realloc(e.eval, len + 1, ft_strlen(src) + 1);	
				}
				if (IS_QUOTE(src[i]) && src[i - 1] == '\\')
				{
					src = ft_delchar_n(src, i - 1);
					e.eval[i] = 'q';
				}
			}
			e.eval[save] = ' ';
			e.eval[i] = ' ';
		}
		else
			e.eval[i] = 'e';
	}
	e.s = src;
	e.eval[i] = 0;
	return (e);
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
	t_eval e;

	if (!input|| !*input)
		return (NULL);
	e = analyse(input);
	head = ft_get_words(e.s, e.eval);
	ft_strdel(&e.eval);
	ft_strdel(&e.s);
	return (head);
}