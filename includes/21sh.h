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
	int				ret;
	enum e_type		o_type;    //op
	struct s_tree	*next; 
}				t_tree;



t_tree 		*get_tree(char *input);
void 		ft_free_tree(t_tree *t);

//exec redirection
int ft_redirect(t_tree *t);
int ft_redirect_builtin(t_tree *t, int fd[3]);
void ft_reset_fd(int fd[3]);


t_tree *exec_pipe(t_tree *t);
t_tree *exec_instruction(t_tree *t);
int  run_builtin(t_tree *t);
void exec_tree(t_tree *t);


t_tree	*ft_get_set_tree(t_tree *new_t);
void 	set_signals(void);







//builtins
int		check_builtin(char **input);
t_envv	*ft_cd(char **input, t_envv *envv);
void	ft_echo(char **input);
void	ft_env(t_tree *t, t_envv *envv);

//sys
int fd_dup(int fd1, int fd2);
char	*get_bin_path(char *input, t_envv *envv);
int ft_execve(t_tree *t);
int ft_execve_pipe(t_tree *t);

#endif
