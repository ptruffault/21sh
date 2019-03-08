/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/19 13:17:03 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL42_H
# define SHELL42_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/includes/libft.h"
# include "termios.h"
# include <termios.h>
# include <term.h>
# include "structures.h"
# include <pwd.h>

char		ft_parse_back(char c);
void		ft_execve_pip(t_process *p, t_shell *sh, t_tree *t, int mode);
void		ft_delete_char(t_eval *e);
char		*ft_update_pwd(t_shell *sh);
t_redirect	*parse_heredoc(t_redirect *new, t_word *w);
void		init_env(t_shell *sh, char **argv);
t_word		*ft_deltword(t_word *prev, t_word *src);
void		ft_free_thist(t_hist *h);
void		ft_free_redirection(t_redirect *r);
void		ft_free_tword(t_word *w);
void		ft_free_tprocess(t_process *p);
void		ft_free_tshell(t_shell *sh);
void		ft_disp(t_shell *sh);
char		*get_input(void);
char		**ft_twordto_arr(t_word *w);
void		ft_put_tword(t_word *w);
t_word		*ft_expention(t_word *w);
char		*ft_exp_var(char *ret, t_shell *sh);
int			get_content_size(char *s);
char		*ft_exp_param(char *ret, t_shell *sh, char *ptr);
char		*ft_exp_home_var(char *ret, char *ptr, t_envv *envv);
char		*ft_exp_envv_var(char *ret, char *ptr, t_shell *sh);
char		*ft_exp_end(char *ret, char *ptr, char *value, char *parenth);
char		*ft_get_len(char *value);
char		*ft_exp_param_sub(char *parenth, t_shell *sh);
char		*ft_get_secondvalue(char *src);
char		*ft_cut_string(char *parenth, char *val, int *curr);
t_tree		*get_tree(char *input);
void		ft_free_tree(t_tree *t);
int			ft_redirect(t_tree *t);
int			ft_redirect_builtin(t_tree *t, t_process *p);
int			get_destination_fd(t_redirect *r);
void		ft_reset_fd(t_process *p);
int			fd_dup(int fd1, int fd2, t_process *p, int close);
t_shell		*ft_get_set_shell(t_shell *sh);
void		reset_term(void);
void		init_shell(t_shell *sh, char **envv, char **argv);
void		set_signals(void);
int			ft_execve(t_process *p, t_shell *sh, t_tree *t);
t_tree		*exec_pipe(t_tree *t);
void		ft_exec_son(t_process *p, t_tree *t, t_shell *sh);
t_tree		*exec_instruction(t_tree *t);
int			run_builtin(t_tree *t, char **argv, t_shell *sh);
t_tree		*exec_tree(t_tree *t);
int			exec_file(char *path, t_shell *sh);
int			exec_fd(t_shell *sh, int fd);
t_tree		*ft_get_set_tree(t_tree *new_t);
int			new_process(t_process *new, t_tree *t, t_shell *sh);
void		ft_add_process(t_shell *sh, t_process *new);
int			kill_running_fg_process(t_process *p, int sig);
t_process	*ft_get_process(t_process *p, int pid);
t_process	*ft_get_running_process(t_process *p);
char		*search_in_envv(char *input, t_envv *envv);
char		*absolute_path(char *input, t_envv *envv);
char		*get_bin_path(char *input, t_envv *envv);
int			ft_check_ascii(char *input);
int			ft_isparenth(char c);
int			ft_setup_edit_term(t_shell *sh);
void		ft_set_old_term(t_shell *sh);
void		ft_update_windows(t_edit *e);
void		init_termcaps(t_shell *sh);
int			check_builtin(char *input);
t_envv		*ft_cd(char **input, t_envv *envv);
t_envv		*change_dir(char *path, t_envv *envv);
int			ft_echo(char **input);
void		ft_exit(char *nbr);
int			ft_env(t_envv *envv, char **argv);
t_envv		*ft_export(t_shell *sh, char **argv);
void		ft_alias(t_shell *sh, char **argv);
void		ft_jobs(t_shell *sh);
int			ft_type(t_word *w);
int			putword(t_word *w, int t);
int			putfile(t_word *w, t_envv *env, int t);
int			putcmd(t_word *w, t_envv *env, int t);
int			putbuiltin(t_word *w, int t);
int			putalias(t_word *w, t_envv *alias, int t);
t_hist		*init_hist(char *hist);
int			ft_hist_len(t_hist *hist);
t_hist		*new_hist(void);
t_hist		*add_hist(t_hist *head, char *s);
void		ft_lex_backslash(t_eval *e);
void		ft_lex_parenth(t_eval *e);
void		ft_lex_var(t_eval *e);
void		ft_lex_dquote(t_eval *e);
void		ft_lex_quote(t_eval *e);
t_word		*ft_check_alias(t_word *head, t_shell *sh);
t_word		*ft_addtword(t_word *head, t_word *new);
t_word		*get_redirections(t_tree *t, t_word *w);
t_tree		*new_tree(void);
t_redirect	*new_redirection(void);
t_tree		*add_newttree(t_tree *tree, t_word *w);
t_word		*ft_get_words(t_eval *e);
t_eval		lexer(char *src);
t_word		*eval_line(char *input);
t_word		*new_tword(void);
char		*heredoc_get_input(char *eoi, t_shell *sh);
t_word		*o_get_input(int type);
char		*q_get_input(char c);
char		*p_get_input(char c);
char		*backslash_get_input(void);
t_process	*init_process(t_tree *t, t_shell *sh);
void		ft_delete_process(int pid);

#endif
