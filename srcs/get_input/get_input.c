/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:12:58 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/13 13:12:59 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_input.h>

/*void get_hist_path(t_edit *e)
{
	int x;
	char *buff;
	static char *hist_path = 0;

	if (hist_path != 0)
		{
			e->path_hist = hist_path;
			return;
		}
	x = 2;
	if (!(buff = malloc(sizeof(char) * x)))
		exit(0);
	while (!getcwd(buff, x))
		{
			x = x * 2;
			free(buff);
			if (!(buff = malloc(sizeof(char) * (x * 2))))
				exit(0);
		}
		e->path_hist = ft_strjoin(buff, "/.21sh_history");
		free(buff);
		return;
}*/

char	*get_input(void)
{
	t_shell 		*sh;
	t_edit			e;
	char			*ret;
	unsigned long	buf;

	sh = ft_get_set_shell(NULL);
	e = init_tedit(sh->env);
	e.pos_hist = 0;
	e.hist = sh->hist;
	while (e.edited == FALSE)
	{
		buf = 0;
		read(0, &buf, 8);
		handle_input(buf, &e);
	}
	//printf("tawdaw\n");
	if (e.input[0] != '\0')
	{
		printf("hein?%s|\n", get_tenvv_val(sh->env, "HISTORY"));
		ft_write_in_file(get_tenvv_val(sh->env, "HISTORY"), e.input);
		sh->hist = add_hist(sh->hist, e.input);
	}
	//printf("test\n");
	ret = ft_strdup(e.input);
	free_tedit(&e);
	//printf("trois\n");
	ft_putchar('\n');
	return (ret);
}
