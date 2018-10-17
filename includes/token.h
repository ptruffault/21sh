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


typedef struct s_instruct
{
	char *bin_path;
	char **args;
	char *r;
	struct s_instruct *next;
}				t_instruct;


# define IS_TOKEN(x) (IS_REDIRECTION(x) || x == ';')
# define IS_REDIRECTION(x) (x == '|' || x == '>' || x == '<')



t_token *new_token(t_token *prev);

#endif