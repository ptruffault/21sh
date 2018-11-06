#include "../includes/21sh.h"

void ft_free_tree(t_tree *t)
{
	t_tree *tmp;

	while (t)
	{
		ft_freestrarr(t->arr);
		ft_strdel(&t->r);
		ft_strdel(&t->r_path);
		tmp = t->next;
		free(t);
		t = tmp;
	}
}

void print_tree(t_tree *t)
{
	ft_putstr("instruc = ");
	ft_putstrarr(t->arr);
	ft_putchar('\n');
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
	if (t->l)
	{
		printf("link %c\n", t->l);
		
	}
	ft_putchar('\n');
}

static t_tree *new_tree(void)
{
	t_tree *n;

	if (!(n = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	n->arr = NULL;
	n->r = NULL;
	n->l = 0;
	n->r_path = NULL;
	n->next = NULL;
	return (n);
}

static t_tree *init_tree(char **input)
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


static char *get_binpath(char **input, t_envv *e, int *i)
{
	int inf;
	char *ret;

	inf = check_builtin(&input[*i]);
	if (inf == 1)
		 ret = ft_strdup(input[*i]);
	else if (inf == 0)
		 ret = check_bin(input[*i], e);
	*i = *i + 1;
	if (!ret)
		while ((input[*i]) && !IS_EOI(input[*i]) && !IS_PIPE(input[*i]))
			*i = *i + 1;
	return (ret);
}


static char **get_array(char **input, t_envv *e, int *i)
{
	char **ret;
	int len;
	int j;

	len = 0;
	j = 1;
	while (input[*i + len] && !IS_SYNTAX(input[*i + len]))
		len++;
	if (!(ret = (char **)malloc(sizeof(char *) *(len + 1)))
	|| (!(ret[0] = get_binpath(input, e, i))))
	{
		*i = *i + len;
		return (NULL);
	}
	while (j < len)
	{
		ret[j++] = ft_strdup(input[*i]);
		*i = *i + 1;
	}
	ret[j] = NULL;
	return (ret);
}


static void eval_tree(t_tree *t, char **input, t_envv *e)
{
	t_tree *tmp;
	int arr_len;
	int i;

	i = 0;
	tmp = t;
	arr_len = ft_strarrlen(input);
	while (i < arr_len)
	{
		if ((tmp->arr = get_array(input, e, &i)))
			tmp = get_redirection(tmp, input, &i);
		print_tree(tmp);
		if (t->l &&  (tmp->next))
		{
			tmp = tmp->next;
			i++;
		}
	}
}

t_tree *get_tree(char *input, t_envv *e)
{
	t_tree	*tree;
	char 	**t;

	if (!(input = correct_syntax(input)))
		return (NULL);
	t = ft_correct(ft_strsplit_word(input), e);
	ft_strdel(&input);
	if ((tree = init_tree(t)))
		eval_tree(tree, t, e);
	ft_freestrarr(t);
	return (tree);
}

