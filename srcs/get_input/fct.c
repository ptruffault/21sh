#include <get_input.h>


int ft_isparenth(char c)
{
	if (c == '{' || c == '(')
		return (1);
	else if (c == '}' || c == ')')
		return (2);
	return (0);
}

t_hist *new_thist(void)
{
	t_hist *n;

	if (!(n = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	n->s =NULL;
	n->next = NULL;
	return (n);
}

void put_thist(t_hist *h)
{
	int i;

	i = 0;
	while (h)
	{
		ft_printf("{%i} -> %s", i++, h->s );
		h = h->next;
	}
}


t_hist *init_thist(t_envv *env)
{
	t_hist *new;
	t_hist *tmp;
	char **arr;
	char *h_path;
	int i;

	h_path = NULL;
	new = NULL;
	if ((h_path = get_tenvv_val(env,  "HISTORY"))
	&& (arr = ft_get_txt(open(h_path,  O_WRONLY | O_CREAT, S_IRWXU)))
	&& (new = new_thist()) && (i = ft_strarrlen(arr)) > 0)
	{
		tmp = new;
		while (i > 0)
		{
			tmp->s = ft_strdup(arr[i--]);
			tmp = tmp->next;
			if (i > 0)
				tmp = new_thist();
		}
	}
	return (new);
}
