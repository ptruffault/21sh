/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/03 13:38:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEUR_H
# define PARSEUR_H
# include "21sh.h"

# define S_UNDEF 0
# define S_DQUOTE 1
# define S_QUOTE 2
# define S_VAR 3

typedef struct 	s_eval
{
	char *s;
	int status;
	char *eval;
	int curr;
}				t_eval;

typedef struct s_word
{
	enum e_type 	type;
	char 			*word;
	int 			position;
	struct s_word 	*next;
}				t_word;

t_word 		*get_redirections(t_tree *t, t_word *w);
t_tree 		*new_tree(void);
t_redirect 	*new_redirection(void);
t_eval 		lexer(char *src);
t_word 		*eval_line(char *input);
void 		ft_free_tword(t_word *w);
t_word 		*new_tword(void);
char 		*heredoc_get_input(char *eoi);
t_word 		*o_get_input(int type);
char 		*q_get_input(char c);
char 		*backslash_get_input(void);

#endif