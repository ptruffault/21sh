/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-rosa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:44:14 by adi-rosa          #+#    #+#             */
/*   Updated: 2019/02/08 14:44:16 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TENVV_H

# define TENVV_H
# include "libft.h"
# define USER "ptruffau"
# define HOME "/Users/ptruffau/"

typedef struct s_envv	t_envv;

struct	s_envv
{
	char	*name;
	char	*value;
	t_envv	*next;
};

t_envv	*ft_get_set_envv(t_envv *t);
t_envv	*ft_new_envv(t_envv *envv, char *name, char *value);
t_envv	*ft_setenv(t_envv *envv, char **t);
t_envv	*ft_unsetenv(t_envv *envv, char **t);
t_envv	*ft_del_envv(t_envv *envv, char *name);
char	*get_value(char *equal);
char	*get_name(char *equal);
void	ft_puttenvv(t_envv *envv);
void	del_tenvv(t_envv *envv);
void	ft_free_tenvv(t_envv *envv);
t_envv	*new_tenvv(void);
t_envv	*ft_changetenvv_val(t_envv *envv, char *name, char *new_val);
char	*get_tenvv_val(t_envv *envv, char *name);
t_envv	*get_tenvv(t_envv *envv, char *name);
t_envv	*ft_tenvv_cpy(t_envv *src);
char	**tenvv_to_tab(t_envv *envv);
t_envv	*init_tenvv(char **tab_envv);

#endif
