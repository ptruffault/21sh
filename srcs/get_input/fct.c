#include "../../includes/get_input.h"


int ft_isparenth(char c)
{
	if (c == '{' || c == '(')
		return (1);
	else if (c == '}' || c == ')')
		return (2);
	return (0);
}

t_hist *new_hist(void)
{
	t_hist *n;

	if (!(n = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	n->s =NULL;
	n->next = NULL;
	return (n);
}

void put_hist(t_hist *h)
{
	int i;

	i = 0;
	while (h)
	{
		ft_printf("{%i} -> %s", i++, h->s );
		h = h->next;
	}
}

t_hist *add_hist(t_hist *head, char *s)
{
	t_hist *new;

	if (!(new = new_hist()))
		return (NULL);
	new->s = ft_strdup(s);
	new->next = head;
	return (new);
}


t_hist *init_hist(t_envv *env)
{
	t_hist *new;
	t_hist *tmp;
	int fd;
	char **arr;
	int i;

	new = NULL;
	if ((fd = open(get_tenvv_val(env,  "HISTORY"), O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) > 0)
	{
		if((arr = ft_get_txt(fd)) && (new = new_hist()) && (i = ft_strarrlen(arr) - 1) > 0)
		{
			tmp = new;
			while (i > 0)
			{
				tmp->s = ft_strdup(arr[i--]);
				tmp->next = new_hist();
				tmp = tmp->next;
			}
			ft_freestrarr(arr);
		}
		ft_close(fd);
	}
	else
		perror(get_tenvv_val(env,  "HISTORY"));
	return (new);
}
