/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2018/12/03 13:38:41 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_21SH_H
# define MY_21SH_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/includes/libft.h"
# define IS_STD(x) (0 <= x && x <= 2)
# define IS_CMD(x) (1 <= x && x <= 4)

enum e_rtype{
	UNDEF = 0,
	R_LEFT = 1,
    R_RIGHT = 2,
   	R_DLEFT = 3,
    R_DRIGHT = 4
};

enum e_otype{
	UN = 0,
	O_AND = 1,
    O_OR = 2,
    O_SEP = 3, 
    O_PIPE = 4
};

enum e_wtype{ 
    undef = 0,
    CMD = 1,
    PATH = 2,
    QUOTE = 3,
    VAR = 4,
    REDIRECT = 5,
    OPERATEUR = 6
};

typedef struct	s_hist
{
	char *s;
	struct s_hist *next;
}				t_hist;



typedef struct 	s_eval
{
	char *s;
	int status;
	char *eval;
	int curr;
}				t_eval;

typedef struct s_word
{
	enum e_wtype 	type;
	char 			*word;
	struct s_word 	*next;
}				t_word;


typedef struct s_redirect
{
	enum e_rtype 		t;
	char 				*path;
	int 				from;
	int 				to;
	char				*heredoc;
	int 				done;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_tree
{
	t_word 			*cmd;
	t_redirect		*r;
	int				ret;
	enum e_otype	o_type;
	struct s_tree	*next; 
}				t_tree;

typedef struct s_shell
{
	t_envv *env;
	t_envv *intern;
	t_envv *alias;
	t_hist *hist;
}				t_shell;

char **ft_twordto_arr(t_word *w);
t_word *ft_expention(t_word *w);
char  *ft_exp_var(char *ret, t_shell *sh);

t_tree 		*get_tree(char *input);
void 		ft_free_tree(t_tree *t);

//redirection
int ft_redirect(t_tree *t);
int ft_redirect_builtin(t_tree *t, int fd[3]);
void ft_reset_fd(int fd[3]);

t_shell 	*ft_get_set_shell(t_shell *sh);
void 		init_shell(t_shell *sh, char **envv, char **argv);
void 	set_signals(void);

//exec
t_tree *exec_pipe(t_tree *t);
t_tree *exec_instruction(t_tree *t);
int  run_builtin(t_tree *t, char **argv);
t_tree *exec_tree(t_tree *t);
void exec_file(char *path, t_shell *sh);
t_tree	*ft_get_set_tree(t_tree *new_t);



char	*search_in_envv(char *input, t_envv *envv);
char	*absolute_path(char *input, t_envv *envv);
char	*get_bin_path(char *input, t_envv *envv);

//fct.c
int ft_isparenth(char c);



//builtins
int		check_builtin(char *input);
t_envv	*ft_cd(char **input, t_envv *envv);
void	ft_echo(char **input);
void	ft_env(t_envv *envv, char **argv);
t_envv *ft_export(t_shell *sh, char **argv);
t_envv *ft_alias(t_shell *sh, char **argv);
void ft_type(t_word *w);

//sys
int fd_dup(int fd1, int fd2);
int ft_execve(t_tree *t);

//historique
t_hist *init_hist(t_envv *env);
t_hist *new_hist(void);
t_hist *add_hist(t_hist *head, char *s);
#endif
