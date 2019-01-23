/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 12:57:16 by ptruffau          #+#    #+#             */
/*   Updated: 2019/01/23 12:52:45 by adi-rosa         ###   ########.fr       */
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
# include "21sh.h"
# include "../libft/includes/libft.h"
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
# define TERM(x) ft_putstr(tgetstr(x, NULL))
# define CURSEUR_UP "up"
# define CURSEUR_DO "do"
# define CURSEUR_LE "le"
# define CURSEUR_RI "nd"
# define CURSEUR_MOVE "cm"
# define SAVE_CURS  "sc"
# define RESET_CURS "rc"
# define CLEAR "cl"
# define UNDERLINE_CURS "uc"
# define DELETE_LINE "dl"

/* DEFINE DE TESTS */

# define TOUCHE_MAJ_ARROW_LEFT 21
# define TOUCHE_MAJ_ARROW_RIGHT 11
# define TOUCHE_CMD_C 1
# define TOUCHE_CMD_V 5


/* DEFINE DE TESTS */

typedef struct	s_termi
{
	struct termios	term;
	int				x;
	int				y;
	int				nb_of_l;
	int				width;
}				t_termi;

typedef struct	s_edit
{
	t_bool	edited;
	char	*input;
	int		curr;
	int		size;
	int		curr_history;
	int		pos_hist;
	int		select;
	char	*clipboard;
	t_hist	*hist;
	t_termi	*t;
}				t_edit;

char			*get_input(void);
void			ft_delete_line(t_edit *e);
void			hist_move_do(t_edit *e);
void			hist_move_up(t_edit *e);
void			delete_on(t_edit *e);
void			delete_left(t_edit *e);
void			ft_add_char(char buf, t_edit *e);
void			curs_move_right(t_edit *e);
void			curs_move_left(t_edit *e);
void			curs_move_to(t_edit *e, int x, int y);
void			curs_reset(t_edit *e);
void			curs_gotoend(t_edit *e);
void			curs_reset(t_edit *e);
void			ft_print_line(t_edit *e);
void			ft_clear(t_edit *e);
void			ft_delete_line(t_edit *e);
void 			add_to_file(char *path, char *s);
void			handle_input(unsigned long buf, t_edit *e);
t_edit			*get_set_edit(t_edit *new_ed);
t_edit			init_tedit(t_envv *env);
void			free_tedit(t_edit *e);
void 			get_hist_path(t_edit *e);
char 			**get_hist(int fd);
void			update_input(t_edit *e, char *s);
void ft_copy(t_edit *e);
void ft_paste(t_edit *e);

void ft_disp(int argc, char **argv);

#endif
