/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 16:02:36 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 16:53:02 by adi-rosa         ###   ########.fr       */
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
# define IS_STD(x) (0 <= x && x <= 2)
# define IS_CMD(x) (1 <= x && x <= 5)
# define IS_EXP(x) (1 <= x && x <= 4)

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
char		*ft_exp_param_sub(char *parenth, t_shell *sh);
t_tree		*get_tree(char *input);
void		ft_free_tree(t_tree *t);
int			ft_redirect(t_tree *t);
int			ft_redirect_builtin(t_tree *t, int fd[3]);
int			get_destination_fd(t_redirect *r);
void		ft_reset_fd(int fd[3]);
int			fd_dup(int fd1, int fd2, int close);
t_shell		*ft_get_set_shell(t_shell *sh);
void		reset_term(void);
void		init_shell(t_shell *sh, char **envv, char **argv);
void		set_signals(void);
int			ft_exec(t_tree *t);
t_tree		*exec_pipe(t_tree *t);
t_tree		*exec_instruction(t_tree *t);
int			run_builtin(t_tree *t, char **argv);
t_tree		*exec_tree(t_tree *t);
void		exec_file(char *path);
t_tree		*ft_get_set_tree(t_tree *new_t);
int			new_process(t_process *new, t_tree *t, t_shell *sh);
void		ft_add_process(t_shell *sh, t_process *new);
int			kill_running_fg_process(t_process *p, int sig);
t_process	*ft_get_process(t_process *p, int pid);
t_process	*ft_get_running_process(t_process *p);
char		*search_in_envv(char *input, t_envv *envv);
char		*absolute_path(char *input, t_envv *envv);
char		*get_bin_path(char *input, t_envv *envv);
int			ft_isparenth(char c);
int			ft_setup_edit_term(t_shell *sh);
void		ft_set_old_term(t_shell *sh);
void		ft_update_windows(t_edit *e);
void		init_termcaps(t_shell *sh);
int			check_builtin(char *input);
t_envv		*ft_cd(char **input, t_envv *envv);
void		ft_echo(char **input);
void		ft_exit(void);
void		ft_env(t_envv *envv, char **argv);
t_envv		*ft_export(t_shell *sh, char **argv);
void		ft_alias(t_shell *sh, char **argv);
void		ft_jobs(t_shell *sh);
void		ft_type(t_word *w);
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
t_word		*ft_get_words(t_eval *e);
t_eval		lexer(char *src);
t_word		*eval_line(char *input);
t_word		*new_tword(void);
char		*heredoc_get_input(char *eoi);
t_word		*o_get_input(int type);
char		*q_get_input(char c);
char		*p_get_input(char c);
char		*backslash_get_input(void);

#endif