#include "../includes/get_input.h"

static void	update_input(t_edit *e, char *s)
{
	ft_delete_line(e);
	ft_strdel(&e->input);
	e->input = s;
	e->size = ft_strlen(s) + 1;
	e->t->nb_of_l = e->size / e->t->width;
	ft_print_line(e);
	e->curr = 0;
	curs_reset(e);
}

char **ft_tab_realloc(char **buff, size_t size)
{
	char **ret;
	int x;

	if (!(ret = malloc(size)))
		return (NULL);
	if (!buff)
		return (buff);
	x = -1;
	while (buff[++x])
	{
		ret[x] = ft_strdup(buff[x]);
		free(buff[x]);
	}
	ret[x] = NULL;
	free(buff);
	return (ret);
}

char **get_hist(int fd)
{
	int x;
	char *line;
	char **hist;

	x = 0;
	/*if ((fd = open(e->path_hist, O_RDONLY)) != -1)
	{
		exit(0);
	}
	x = 0;*/
	hist = NULL;
	while (get_next_line(fd, &line) != -1)
		{
			if (!(hist = ft_tab_realloc(hist, sizeof(char * ) * (x + 2))))
				exit(0);
			hist[x++] = ft_strdup(line);
			ft_strdel(&line);
		}
	if (x > 0)
		hist[x] = NULL;
	close(fd);
	return (hist);
}

void	hist_move_up(t_edit *e)
{
	int x;
	int b;
	t_hist *hist;

/*	if (e->input != NULL && e->curr_history == 0 && (s = ft_search_line_in_file(HISTORY_PATH, e->input)))
	{
		e->curr_history = 0;
		update_input(e, s);
	}
	else if ((s = ft_get_line_in_file(HISTORY_PATH, e->curr_history)))
	{
		e->curr_history++;
		update_input(e, s);
	}*/
	printf("before\n");
	hist = e->hist;
	if (!e->hist || !e->hist->s)
	{
		printf("no history\n");
		return;
	}
	printf("after\n");
	x = 0;
	printf("test\n");
	while (hist->next && x < e->pos_hist)
	{
		hist = hist->next;
		++x;
	}
	printf("wadwad []%d[]\n", x);
	ft_strdel(&e->input);
	if (hist && !(e->input = ft_strnew(ft_strlen(hist->s) + 2)))
		exit(0);
	b = -1;
	while(hist && hist->s[++b])
		e->input[b] = hist->s[b];
	e->pos_hist++;
}

void	hist_move_do(t_edit *e)
{
	t_shell *sh;
	char *hist_path;
	char *s;

	sh = ft_get_set_shell(NULL);
	if ((hist_path = get_tenvv_val(sh->env, "HISTORY"))
	&& (s = ft_get_line_in_file(hist_path, e->curr_history - 1)))
	{
		e->curr_history--;
		update_input(e, s);
	}
}
