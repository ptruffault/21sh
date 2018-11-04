#include "../includes/21sh.h"

static  char **ft_get_file_content(char *path)
{
	int fd;
	char **ret;

	if (!path)
	{
		warning ("file or needed as argument", "< [file] ");
		return (NULL);
	}
	if ((fd = ft_open(path)) > 0)
	{
		ret = ft_get_txt(fd);
		close(fd);
	}
	return (ret);
}

static char **get_arguments_from_input(char **input, int *i)
{
	char **arg;
	int len;
	int j;

	len = 0;
	j = 0;
	if (!(input[*i]) || IS_SYNTAX(input[*i]))
		return (NULL);
	while (input[*i + len] && !IS_SYNTAX(input[*i + len]))
		len++;
	if (!(arg = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	while (j < len)
	{
		arg[j++] = ft_strdup(input[*i]);
		*i = *i + 1;
	}
	arg[j] = NULL;
	return (arg);
}

static char **my_get_input(t_envv *e, char *s)
{
	char **ret;
	char **env;
	int i;

	if (!s)
	{
		warning ("End of instruction string needed as argument", "<< \"EOI\" ");
		return (NULL);
	}
	if (!(ret = (char **)malloc(sizeof(char *))))
		return (NULL);
	i = 0;
	env = tenvv_to_tab(e);
	while (42)
	{
		if (!(ret[i] = get_input(env)) || ft_strequ(ret[i], s))
		{
			ft_freestrarr(env);
			return (ret);
		}
		i++;
		ret = ft_realloc(ret, i , i + 1);
	}
	return (NULL);
}

char  **get_arguments(char **input, int *i, t_envv *e)
{
	char *ptr;
	char **ret;

	ret = get_arguments_from_input(input, i);
	if (input[*i] && (ptr = ft_strchr(input[*i], '<')))
	{
		*i = *i + 1;
		if (*(ptr + 1) == '<')
			ret = ft_strarrjoin_fr(ret, my_get_input(e, input[*i]));
		else
			ret = ft_strarrjoin_fr(ret, ft_get_file_content(input[*i]));
	}
	return(ret);
}


t_tree *get_redirection(t_tree *t ,char **input, int *i)
{
	char *ptr;

	if (!(input[*i]) || !(ptr = ft_strchr(input[*i], '>')))
		return (t);
	t->r = ft_strdup(input[*i]);
	if (*(ptr + 1) == 0 || (*(ptr + 1) == '>' && *(ptr + 2) == 0))
	{
		if (!input[*i + 1])
		{
			warning("redirection need an argument", ">[&Y] [file]");
			ft_strdel(&t->r);
		}
		else
		{
			*i = *i + 1;
			t->r_path = ft_strdup(input[*i]);
		}
	}
	*i = *i + 1;
	return (t);
}