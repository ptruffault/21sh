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



void	ft_disp(t_envv *envv, int argc, char **argv);
void	run_bin(char **args, t_envv *envv);
char	**ft_correct(char **input, t_envv *envv);
char	*correct_syntax(char *s);
t_envv	*read_cmd(t_envv *my_envv, char *input, char **arr);
char	*ft_get_input(void);
int		check_cmd(char *input, t_envv *envv);
char	*check_bin(char *input, t_envv *envv);
int		check_builtin(char **input);
t_envv	*run_builtin(char **input, t_envv *envv, char **arr);
t_envv	*ft_cd(char **input, t_envv *envv);

void	ft_echo(char **input);


void	ft_env(char **input, t_envv *envv);

#endif
