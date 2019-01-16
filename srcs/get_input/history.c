#include "../includes/get_input.h"

static void	update_input(t_edit *e, char *s)
{
	ft_delete_line(e);
	//ft_strdel(&e->input);
	e->input = s;
	e->size = ft_strlen(s) + 1;
	e->t->nb_of_l = e->size / e->t->width;
	ft_print_line(e);
	curs_move_to(e, -1, -1);
	e->curr = e->size - 1;
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
		ft_strdel(&buff[x]);
	}
	ret[x] = NULL;
	free(buff);
	return (ret);
}

/*char **get_hist(int fd)
{
	int x;
	char *line;
	char **hist;

	x = 0;
	if ((fd = open(e->path_hist, O_RDONLY)) != -1)
	{
		exit(0);
	}
	x = 0;
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
}*/

void	hist_move_up(t_edit *e)
{
	int x;
	t_hist *hist;

	hist = e->hist;
	if (!hist || !hist->s)
		return;
	x = 0;
	e->pos_hist++;
	while (hist->next && x++ < e->pos_hist)
		hist = hist->next;
	if (hist && hist->s)
		update_input(e, hist->s);
	/*while(hist && hist->s[++b])
		e->input[b] = hist->s[b];
	e->pos_hist++;
	printf("[%s]\n", e->input);
	ft_print_line(e);*/
}

void	hist_move_do(t_edit *e)
{
	t_hist *hist;
	int x;

	if (e->curr == 0 || !e->hist || !e->hist->s)
		return;
	hist = e->hist;
	hist = e->hist;
	x = 0;
	e->pos_hist--;
	while (x++ < e->pos_hist)
		hist = hist->next;
	if (hist && hist->s)
		update_input(e, hist->s);
}
