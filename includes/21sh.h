/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
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

# define USER "ptruffau"
# define HOME "/Users/ptruffau/"

typedef struct s_envv	t_envv;
struct	s_envv
{
	char	*name;
	char	*value;
	t_envv	*next;
};

void	ft_disp(t_envv *envv, int argc, char **argv);
void	run_bin(char **args, t_envv *envv);
char	**ft_correct(char **input, t_envv *envv);
t_envv	*read_cmd(t_envv *my_envv, char *input, char **arr);
int		check_void_input(char *s);
char	*ft_get_input(void);
t_envv	*init_tenvv(t_envv *envv, char **tab_envv);
int		check_cmd(char *input, t_envv *envv);
char	*check_bin(char **input, t_envv *envv);
int		check_builtin(char **input);
t_envv	*run_builtin(char **input, t_envv *envv, char **arr);
t_envv	*ft_cd(char **input, t_envv *envv);
t_envv	*ft_setenv(t_envv *envv, char *name, char *value);
t_envv	*ft_unsetenv(t_envv *envv, char *name);
t_envv	*get_tenvv(t_envv *envv, char *name);
t_envv	*ft_tenvv_cpy(t_envv *src);
void	error(char *descrpt, char *name);
void	ft_echo(char **input);
void	ft_puttenvv(t_envv *envv);
void	del_tenvv(t_envv *envv);
void	ft_free_tenvv(t_envv *envv);
t_envv	*new_tenvv(void);
t_envv	*ft_changetenvv_val(t_envv *envv, char *name, char *new_val);
char	*get_tenvv_val(t_envv *envv, char *name);
char	*get_value(char *equal);
char	*get_name(char *equal);
char	*get_equal(char *name, char *value);
void	ft_env(char **input, t_envv *envv);

#endif
