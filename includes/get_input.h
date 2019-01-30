
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
# include "21sh.h"
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
# define CURSEUR_UP "up"
# define CURSEUR_DO "do"
# define CURSEUR_LE "le"
# define CURSEUR_RI "nd"
# define CURSOR_MRIGHT "ch"
# define CURSEUR_MOVE "cm"
# define SAVE_CURS  "sc"
# define RESET_CURS "rc"
# define CLEAR "cl"
# define UNDERLINE_CURS "uc"
# define DELETE_LINE "dl"
# define HOME_POS "ho"

/* DEFINE DE TESTS */

# define TOUCHE_SELECT_LEFT 74982532143899 /* MAJ_LEFT */
# define TOUCHE_SELECT_RIGHT 73883020516123 /* MAJ_RIGHT */
# define TOUCHE_CMD_C 1 /* CTRL_A */
# define TOUCHE_CMD_V 5 /* CTRL_E */
# define TOUCHE_JP_MOT_LEFT 11 /* CTRL_U */
# define TOUCHE_JP_MOT_RIGHT 21 /* CTRL_K */


/* DEFINE DE TESTS */

typedef struct	s_termi
{
	int				x;
	int				y;
	int				nb_of_l;
	int				width;
}				t_termi;

typedef struct	s_edit
{
	t_bool	edited;
	char		*input;
	int			curr;
	int			size;
	int			curr_history;
	int			pos_hist;
	int			select;
	char		*clipboard;
	t_hist	*hist;
	t_termi	t;
}				t_edit;

/* arrow_move.c */

void	curr_move_right(t_edit *e);
void	curr_move_left(t_edit *e);
void curs_go_last(t_edit *e);

/* END arrow_move.c */

/* ft_select.c */

void ft_select_right(t_edit *e);
void ft_select_left(t_edit *e);

/* END ft_select.c */

/* clear_and_all.c */

void entry_key(t_edit *e);
void clear_term(t_edit *e);
void reset_input(t_edit *e);
void just_exit(t_edit *e);

/* END clear_and_all.c */

/* ft_cop_pas.c */

void ft_copy(t_edit *e);
void ft_paste(t_edit *e);

/* END ft_cop_pas.c */

/* ft_jump_word.c */

void ft_jp_word_right(t_edit *e);
void ft_jp_word_left(t_edit *e);

/* END ft_jump_word.c */

/* use_termcaps.c */

int term_actions(char *cmd);
int term_goto(char *cmd, int row, int col);

/* END use_termcaps.c	*/


char			*get_input(void);
void			ft_delete_line(t_edit *e);
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
void 			add_to_file(char *path, char *s);
int				handle_input(unsigned long buf, t_edit *e);
t_edit			*get_set_edit(t_edit *new_ed);
t_edit			init_tedit(void);
void			free_tedit(t_edit *e);
void 			get_hist_path(t_edit *e);
char 			**get_hist(int fd);
void			update_input(t_edit *e, char *s);
void 			ft_disp(int argc, char **argv);

#endif