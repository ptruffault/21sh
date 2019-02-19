/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuctures.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:16:37 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/07 16:16:39 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define IS_STD(x) (0 <= x && x <= 2)
# define IS_CMD(x) (1 <= x && x <= 5)
# define IS_EXP(x) (1 <= x && x <= 4)

enum	e_rtype{
	UNDEF = 0,
	R_LEFT = 1,
	R_RIGHT = 2,
	R_DLEFT = 3,
	R_DRIGHT = 4
};
enum	e_otype{
	UN = 0,
	O_AND = 1,
	O_OR = 2,
	O_SEP = 3,
	O_PIPE = 4,
	O_BACK = 5
};
enum	e_wtype{
	undef = 0,
	CMD = 1,
	ARG = 2,
	DQUOTE = 3,
	VAR = 4,
	QUOTE = 5,
	REDIRECT = 6,
	OPERATEUR = 7
};

enum	e_pstatus{
	RUNNING_FG = 0,
	RUNNING_BG = 1,
	DONE = 2,
	SUSPENDED = 3,
	KILLED = 4
};

enum	e_error
{
	OK = 0,
	SYNTAX = 1,
	OA_MISS = 2,
	OO_MISS = 3,
	OP_MISS = 4,
	Q_MISS = 5,
	DQ_MISS = 6,
	B_MISS = 7,
	P_MISS = 8,
};

typedef struct	s_hist
{
	char			*s;
	struct s_hist	*next;
}				t_hist;

typedef struct	s_edit
{
	t_bool		edited;
	char		*input;
	int			curr;
	int			pos;
	int			width;
	int			pos_hist;
	int			select;
	t_hist		*hist;
}				t_edit;

typedef struct	s_eval
{
	char			*s;
	char			*eval;
	enum e_error	err;
	char			c;
	int				curr;
}				t_eval;

typedef struct	s_word
{
	enum e_wtype	type;
	char			*word;
	struct s_word	*next;
}				t_word;

typedef struct	s_redirect
{
	enum e_rtype		t;
	char				*path;
	int					from;
	int					to;
	char				*heredoc;
	struct s_redirect	*next;
}				t_redirect;

typedef struct	s_tree
{
	t_word			*cmd;
	t_redirect		*r;
	int				ret;
	enum e_otype	o_type;
	struct s_tree	*next;
}				t_tree;

typedef struct	s_process
{
	int					fd[3];
	t_bool				builtins;
	char				*cmd;
	enum e_pstatus		status;
	char				**argv;
	int					pid;
	int					ret;
	struct s_process	*next;
}				t_process;

typedef struct	s_shell
{

	int				heredoc;
	t_envv			*env;
	t_envv			*intern;
	t_envv			*alias;
	t_hist			*hist;
	t_process		*process;
	t_edit			e;
	char			*clipboard;
	struct termios	term;
	struct termios	*saved_term;
}				t_shell;
#endif