/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 16:02:37 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "../libft/includes/libft.h"

enum r_types
{
	>, >>, <, <<, |, ?
};

typedef struct s_redirect
{
	enum	r_type t;
	int		fd_from;
	int		fd_to;
	char 	*file_path;
};

typedef struct s_cmd
{
	char *bin_path;
	char **arr;
}				t_cmd;

typedef struct s_token
{
	
}				t_token;

typedef struct s_syntax
{
	t_token *t;
	t_cmd *cmd;
	struct s_syntax *prev;
	struct s_syntax *next;
}				t_syntax;
# define IS_TOKEN(x) (IS_REDIRECTION(x) || x == ';')
# define IS_REDIRECTION(x) (x == '|' || x == '>' || x == '<')



t_token *new_token(t_token *prev);

#endif