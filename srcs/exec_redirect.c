#include "../includes/21sh.h"

char **my_get_input(t_envv *e, char *s)
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
			ret[i] = NULL;
			return (ret);
		}
		i++;
		ret = ft_realloc(ret, i , i + 1);
	}
	return (NULL);
}


static void get_destination_fd(t_redirect *r)
{	
	if ((r->t == R_RIGHT && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU)) == -1)
	|| (r->t == R_DRIGHT && r->to == -2 && (r->to = open(r->path, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) == -1)
	|| (r->t == R_LEFT && r->from == -1 && (r->from = open(r->path, O_WRONLY , S_IRWXU)) == -1))
	{
 		warning("can't open this file", r->path);
		perror(NULL);
	}
	else if (r->to < 0 && (r->to = open("/dev/null", O_WRONLY | O_CREAT, S_IRWXU)) == -1)
		warning("can't write in /dev/null file", NULL);
	printf("from %i to %i\n",r->from, r->to );
}



t_envv *ft_exec_redirection(t_tree *t, t_envv *e, t_redirect *r)
{
	int save[2];

	put_redirect(r);
	if (r->to < 0 || r->from < 0)
		get_destination_fd(r);
	if (r->to >= 0 && r->from >= 0)
	{
		if ((0 <= r->from && r->from <= 2 && (save[0] = dup(r->from)) == -1)
		|| (0 <= r->to && r->to <= 2 && (save[1] = dup(r->to)) == -1))
			error("impossible to save[0] file descriptor (dup)", "from");
		else if (dup2(r->to, r->from) == -1)
			warning("dup2 failed", NULL);
		else if (close(r->to) == -1)
			warning("close failed", NULL);
		{
	
			e = ft_exec(t, e, r->next);
			if (close(r->from) == -1)
				warning("redirection can't close fd", "from");
			if ((0 <= r->from && r->from <= 2 && (r->from = dup(save[0]) == -1))
			|| (0 <= r->to && r->to <= 2 && (r->to = dup(save[1]) == -1)))
				warning("impossible to load old fd", NULL);
		}
		if (0 <= r->from && r->from <= 2 && close(save[0]) == -1)
			warning("redirection can't close fd", "save");

	}
			printf("just before exec from %i to%i\n", r->from, r->to);
	return (e);
}


t_envv *exec_pipe(t_tree *t, t_envv *e)
{
	int			pipes[2];
	int			pid[2];

	if (pipe(pipes) != 0)
	{
		warning("pipe error", NULL);
		return (e);
	}
	if ((pid[0] = fork()) < 0)
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[0] == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		e = ft_exec(t, e, t->r);
		ft_free_tree(t);
		ft_free_tenvv(e);
		exit(0);
	}
	if ((pid[1] = fork()) < 0)
		error("fork filed to create a new process in pipe", *t->arr);
	else if (pid[1] == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[1]);
		e = exec_instruction(t->next, e);
		ft_free_tree(t);
		ft_free_tenvv(e);
		exit(0);
	} 
	close(pipes[0]);
	close(pipes[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (e);
}