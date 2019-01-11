/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

int ft_open_tmpfile(t_envv *env)
{
	int fd;
	char *sys;
	char *path;

	fd = -1;
	if (!(sys = get_tenvv_val(env, "SYS")))
		error("can't find var", "$SYS");
	else if ((path = ft_strjoin(sys, "/.TMP"))
	&& (fd = open(path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU) < 0))
	{
		error("can't open this file", path);
		perror(NULL);
		warning("is $SYS valid ?", sys);
		return (-1);
	}
	return (fd);
}



t_word *ft_exp_cmd(t_word *w, t_shell *sh, char *ptr)
{	
	t_tree *t;
	int fd;
	char *value;

	if ((fd = ft_open_tmpfile(sh->env)) != -1)
	{
		if ((value = ft_strsub(w->word, ptr - w->word + 2, ft_strlen(w->word) - 3)))
		{
			if ((t = get_tree(value)))
			{
				exec_tree(t);
				ft_free_tree(t);
			}
			else
				warning("no t_tree", NULL);
		}
		else
			ft_strdel(&w->word);
		ft_close(fd);
	}
	return (w);
}


t_word *ft_expention(t_word *w)
{
	t_shell *sh;
	t_word *tmp;
	char *ptr;

	if (!(sh = ft_get_set_shell(NULL)))
		return (NULL);
	tmp = w;
	while (tmp)
	{
		if (IS_CMD(tmp->type) && tmp->word)
		{
			if ((ptr = ft_strchr(tmp->word, '$')) && *(ptr + 1) == '(')
				tmp = ft_exp_cmd(tmp, sh, ptr);
			else
				tmp->word = ft_exp_var(tmp->word, sh);
				
		}
		tmp = tmp->next;
	}
	return (w);
}