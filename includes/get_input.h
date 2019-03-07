/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:50:42 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 16:50:48 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_INPUT_H
# define FT_GET_INPUT_H

# include "termios.h"
# include <termios.h>
# include "term.h"
# include <term.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "shell42.h"
# include "../libft/includes/libft.h"
# define FAILURE 0
# define SUCCESS 1
# define KEY_ENTER 0xA
# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define ARROW_LEFT 4479771
# define ARROW_RIGHT 4414235
# define TOUCHE_DELETE 2117294875
# define TOUCHE_CTRL_C 3
# define TOUCHE_CTRL_D 4
# define TOUCHE_CTRL_L 12
# define TOUCHE_CTRL_R 18
# define TOUCHE_SUPPR 127
# define TOUCHE_HOME 4741915
# define TOUCHE_END 4610843
# define TOUCHE_TAB 9
# define TOUCHE_OPT_RIGHT 1130044187
# define TOUCHE_OPT_LEFT 1146821403
# define TOUCHE_OPT_UP 1096489755
# define TOUCHE_OPT_DOWN 1113266971
# define TOUCHE_OPT_V 10127586
# define TOUCHE_OPT_C 42947
# define TOUCHE_OPT_X 8948194
# define TOUCHE_F5 542058306331
# define TOUCHE_F6 542091860763
# define TOUCHE_DEL 2117294875
# define CURSEUR_MOVE "cm"
# define CURSOR_UP "up"
# define CURSOR_DO "do"
# define CURSOR_LE "le"
# define CURSOR_RI "nd"
# define CURSOR_MHORIZ "ch"
# define CURSEUR_MOVE "cm"
# define SAVE_CURS  "sc"
# define RESET_CURS "rc"
# define CLEAR "cl"
# define UNDERLINE_CURS "uc"
# define DELETE_LINE "dl"
# define HOME_POS "ho"
# define TOUCHE_SELECT_LEFT 74982532143899
# define TOUCHE_SELECT_RIGHT 73883020516123
# define TOUCHE_MAJ_END 77181555399451
# define TOUCHE_MAJ_HOME 79380578655003
# define TOUCHE_MAJ_ARROW_UP 71683997260571
# define TOUCHE_MAJ_ARROW_DOWN 72783508888347
# define TOUCHE_CMD_C 1
# define TOUCHE_CMD_V 5

void			curr_move_right(t_edit *e);
void			curr_move_left(t_edit *e);
void			curs_go_last(t_edit *e);

void			ft_select_right(t_edit *e);
void			ft_select_left(t_edit *e);
void			ft_select_end(t_edit *e);
void			ft_select_home(t_edit *e);
void			ft_home_key(t_edit *e);

void			ft_jump_line_down(t_edit *e);
void			ft_jump_line_up(t_edit *e);

void			entry_key(t_edit *e);
void			clear_term(t_edit *e);
void			reset_get_input(t_edit *e);
void			just_exit(t_edit *e);

void			ft_copy(t_edit *e);
void			ft_paste(t_edit *e);

void			ft_jp_word_right(t_edit *e);
void			ft_jp_word_left(t_edit *e);

int				term_actions(char *cmd);
int				term_goto(char *cmd, int row, int col);

void			ft_delete_line(t_edit *e);
void			curr_go_last(t_edit *e);
void			hist_move_do(t_edit *e);
void			hist_move_up(t_edit *e);
void			delete_on(t_edit *e);
void			delete_left(t_edit *e);
void			ft_add_char(char buf, t_edit *e);
void			curs_move_right(t_edit *e);
void			curs_move_left(t_edit *e);
void			curs_move_to(t_edit *e, int pos);
void			curs_reset(t_edit *e);
void			curs_gotoend(t_edit *e);
void			curs_reset(t_edit *e);
void			ft_print_line(t_edit *e);
void			ft_clear(t_edit *e);
void			ft_delete_line(t_edit *e);
void			add_to_file(char *path, char *s);
int				handle_input(unsigned long buf, t_edit *e);
t_edit			*get_set_edit(t_edit *new_ed);
t_edit			init_tedit(t_shell *sh);
void			free_tedit(t_edit *e);
void			get_hist_path(t_edit *e);
char			**get_hist(int fd);
void			update_input(t_edit *e, char *s);

#endif
