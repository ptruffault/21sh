#include <get_input.h>


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
	char **arr;
	char *h_path;
	int i;

	h_path = NULL;
	new = NULL;
	if ((h_path = get_tenvv_val(env,  "HISTORY"))
	&& (arr = ft_get_txt(open(h_path,  O_WRONLY | O_CREAT, S_IRWXU)))
	&& (new = new_hist()) && (i = ft_strarrlen(arr) - 1) > 0)
	{
		printf("here i am\n");
		tmp = new;
		while (i > 0)
		{
			printf("here i am\n");
			tmp->s = ft_strdup(arr[i]);
			tmp->next = new_hist();
			tmp = tmp->next;
			i--;
		}
	}
	put_hist(new);
	return (new);
}
