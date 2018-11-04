#include "../includes/21sh.h"

void ft_free_tree(t_tree *t)
{
	t_tree *tmp;

	while (t)
	{
		ft_strdel(&t->p);
		ft_freestrarr(t->a);
		ft_strdel(&t->r);
		ft_strdel(&t->r_path);
		tmp = t->next;
		free(t);
		t = tmp;
	}
}

void print_tree(t_tree *t)
{
	ft_putstr("path = ");
	ft_putstr(t->p);
	ft_putchar('\n');
	if (t->a)
	{
		ft_putstr("args = ");
		ft_putstrarr(t->a);
		ft_putchar('\n');
	}
	if (t->r)
	{
		ft_putstr("redirection = ");
		ft_putstr(t->r);
		if (t->r_path)
		{
			ft_putchar('\t');
			ft_putendl(t->r_path);
		}
	}
	ft_putchar('\n');
}

static t_tree *new_tree(void)
{
	t_tree *n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->p = NULL;
	n->a = NULL;
	n->r = NULL;
	n->l = 0;
	n->r_path = NULL;
	n->next = NULL;
	return (n);
}

t_tree *init_tree(char **input)
{
	t_tree *head;
	t_tree *t;
	int i;

	i = 1;
	if (!(head = new_tree()))
		return (NULL);
	t = head;
	while (input[i])
	{
		if (IS_PIPE(input[i]) || IS_EOI(input[i]))
		{
			t->l = (IS_PIPE(input[i]) ? '|' : ';');
			t->next = new_tree();
			t = t->next;
		}
		i++;
	}
	return (head);
}
