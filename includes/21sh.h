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
# define IS_PIPE(x) (x && ft_strequ(x, "|"))
# define IS_EOI(x)  (x && ft_strequ(x, ";"))
# define IS_RED(x) (x && (IS_RIGHT_RED(x) || IS_LEFT_RED(x)))
# define IS_RIGHT_RED(x) (x && (ft_strchr(x, '>')))
# define IS_LEFT_RED(x) ((x && ft_strchr(x, '<')))
# define IS_AND(x) (x && ft_strequ(x, "&&"))
# define IS_OR(x) (x && ft_strequ(x, "||"))
# define IS_OPERATEUR(x) (IS_AND(x) || IS_OR(x))
# define IS_SYNTAX(x) (IS_PIPE(x) || IS_EOI(x) || IS_RED(x) || IS_OPERATEUR(x))

typedef struct s_redirect
{
	int					t;
	char 				*path;
	int 				from;
	int 				to;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_tree
{
	char 			**arr; //args
	t_redirect		*r;
	int				ret;
	char			l;    //next cmd link | or ;
	struct s_tree	*next; 
}				t_tree;

t_envv *ft_exec_redirection(t_tree *t, t_envv *e, t_redirect *r);
t_envv *exec_pipe(t_tree *t, t_envv *e);
t_tree	*ft_get_set_tree(t_tree *new_t);
void 	set_signals(void);
t_envv 	*exec_instruction(t_tree *t, t_envv *e);
char 	**get_cmd_and_arg(char **input, int *i);
t_tree *new_tree(void);
void 	ft_free_tree(t_tree *t);
t_tree 	*get_tree(char *input, t_envv *e);
void	 print_tree(t_tree *t);
void 	put_redirect(t_redirect *r);
t_envv *ft_exec(t_tree *t, t_envv *envv, t_redirect *r);
void	ft_disp(t_envv *envv, int argc, char **argv);
void	run_bin(char **args, t_envv *envv);
char	**ft_correct(char **input, t_envv *envv);
char	*correct_syntax(char *s);
char	*ft_get_input(void);

char	*get_bin_path(char *input, t_envv *envv);
int		check_builtin(char **input);
t_envv	*run_builtin(t_tree *t, t_envv *envv);
t_envv	*ft_cd(char **input, t_envv *envv);
void	ft_echo(char **input);
void	ft_env(t_tree *t, t_envv *envv);

#endif
