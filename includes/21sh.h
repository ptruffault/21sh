/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 16:02:37 by ptruffau         ###   ########.fr       */
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
# define IS_PIPE(x) (ft_strequ(x, "|"))
# define IS_EOI(x)  (ft_strequ(x, ";"))
# define IS_RED(x) (IS_RIGHT_RED(x) || IS_LEFT_RED(x))
# define IS_RIGHT_RED(x) ((ft_strchr(x, '>')))
# define IS_LEFT_RED(x) ((ft_strchr(x, '<')))
# define IS_SYNTAX(x) (IS_PIPE(x) || IS_EOI(x) || IS_RED(x))

typedef struct s_tree
{
	char 			**arr; //args
	char 			*r; // redirection [X]>[>][&Y]
	char 			*r_path;
	char			l;    //next cmd link | or ;
	struct s_tree	*next; 
}				t_tree;


t_envv *exec_instruction(t_tree *t, t_envv *envv);
char **get_cmd_and_arg(char **input, t_envv *e, int *i);
t_tree *new_tree(void);
void ft_free_tree(t_tree *t);
t_tree *get_tree(char *input, t_envv *e);
void print_tree(t_tree *t);


void	ft_disp(t_envv *envv, int argc, char **argv);
void	run_bin(char **args, t_envv *envv);
char	**ft_correct(char **input, t_envv *envv);
char	*correct_syntax(char *s);
t_envv	*read_cmd(t_envv *my_envv, char *input, char **arr);
char	*ft_get_input(void);
int		check_cmd(char *input, t_envv *envv);
char	*check_bin(char *input, t_envv *envv);
int		check_builtin(char **input);
t_envv	*run_builtin(t_tree *t, t_envv *envv);
t_envv	*ft_cd(char **input, t_envv *envv);

void	ft_echo(char **input);


void	ft_env(t_tree *t, t_envv *envv);

#endif
