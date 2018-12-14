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

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define IS_STD(fd) (0 <= fd && fd <= 2)


# define IS_OPERATEUR(x) (1 <= x && x <= 4)
# define IS_REDIRECTION(x) (5 <= x && x <= 8)
# define IS_CMD(x) (9 <= x && x <= 11)



enum e_type{ 
    undef = 0, // undef => 'parse error near {}   ' 
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
  };

typedef struct s_word
{
	enum e_type 	type;
	char 			*word;
	int 			position;
	struct s_word 	*next;
}				t_word;


typedef struct s_redirect
{
	enum e_type 		t;
	char 				*path;
	int 				from;
	int 				to;
	char				*heredoc;
	int 				done;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_tree
{
	char 			**arr; //args
	t_redirect		*r;
	int 			fd[3];
	int				ret;
	enum e_type		o_type;    //op
	struct s_tree	*next; 
}				t_tree;

//exec redirection
void reset_fd(t_tree *t);
void ft_redirect(t_tree *t);



t_tree *ft_exec_redirection(t_tree *t, t_redirect *r);
t_tree *exec_pipe(t_tree *t);
t_tree *exec_instruction(t_tree *t);
void ft_exec(t_tree *t);
void  run_builtin(t_tree *t);
void exec_tree(t_tree *t);


t_tree	*ft_get_set_tree(t_tree *new_t);
void 	set_signals(void);

t_word 		*get_redirections(t_tree *t, t_word *w);
t_tree 		*new_tree(void);
void 		ft_free_tree(t_tree *t);
void 		ft_free_redirection(t_redirect *r);
t_redirect 	*new_redirection(void);
t_tree 		*get_tree(char *input);

char 		*heredoc_get_input(char *eoi);
t_word 		*o_get_input(int type);
t_word 		*eval_line(char *input);
void 		ft_free_tword(t_word *w);
t_word 		*new_tword(void);


void	ft_disp(t_envv *envv, int argc, char **argv);

char	*ft_get_input(void);


//builtins
int		check_builtin(char **input);
t_envv	*ft_cd(char **input, t_envv *envv);
void	ft_echo(char **input);
void	ft_env(t_tree *t, t_envv *envv);

//sys
int fd_dup(int fd1, int fd2);
char	*get_bin_path(char *input, t_envv *envv);
int ft_execve(char **argv, t_envv *e);

#endif
