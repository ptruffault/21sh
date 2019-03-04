
#include "../includes/shell42.h"


static char	*get_shell_path(char *path, char *pwd)
{
	if (*path == '/')
		return (ft_strdup(path + 1));
	if (ft_str_startwith(path, "./"))
		return (ft_strjoin(pwd, path + 1));
	return (NULL);
}

static void	ft_update_shelvl(t_shell *sh)
{
	t_envv	*shell_lvl;
	char	*nbr;
	int		lvl;

	if ((shell_lvl = get_tenvv(sh->env, "SHLVL")))
		lvl = ft_atoi(shell_lvl->value);
	else
		lvl = 0;
	nbr = ft_itoa(lvl + 1);
	sh->env = ft_new_envv(sh->env, "SHLVL", nbr);
	ft_strdel(&nbr);
}

static void ft_setup_user(t_shell *sh)
{
	struct passwd *user;
	char *user_name;

	if ((user_name = get_tenvv_val(sh->env, "USER")) && 
	(user = getpwnam(user_name)) &&  user->pw_dir)
		sh->env = ft_new_envv(sh->env, "HOME", user->pw_dir);
}

static void ft_setup_env(t_shell *sh, char *shell_fold)
{
	char *hi_path;
	char *rc_path;
	
	sh->env = ft_new_envv(sh->env, "SHELL_FOLD", shell_fold);
	if ((hi_path = ft_strjoin(shell_fold, "/sys/.21history"))
	&& (sh->env = ft_new_envv(sh->env, "HISTORY", hi_path)))
	{
		sh->hist = init_hist(hi_path);
		ft_strdel(&hi_path);
	}
	ft_update_shelvl(sh);
	if ((rc_path = ft_strjoin(shell_fold, "/sys/.21shrc")))
	{
		exec_file(rc_path);
		ft_strdel(&rc_path);
	}
}

void	init_env(t_shell *sh, char **argv)
{
	char *shell_fold;
	char *shell_path;
	char buff[4097];
	char *pwd;

	sh->env = ft_new_envv(sh->env, "TERM", "xterm-256color");
	pwd = getcwd(buff, 4096);
	sh->env = ft_new_envv(sh->env, "PWD", pwd);
	if ((shell_path = get_shell_path(*argv, pwd))
	&& (shell_fold = ft_get_prev_path(shell_path)))
	{
		sh->env = ft_new_envv(sh->env, "SHELL", shell_path);
		ft_setup_env(sh, shell_fold);
		ft_strdel(&shell_fold);
		ft_strdel(&shell_path);
	}
	ft_setup_user(sh);
}