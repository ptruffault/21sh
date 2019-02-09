/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:55:59 by ptruffau          #+#    #+#             */
/*   Updated: 2018/10/04 17:56:02 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>
# include <limits.h>
# define TEST(x) ((ft_strchr("#0 -+.0123456789lhjtz", x)) || TEST_SPEC(x))
# define TEST_SPEC(x) (TEST_SPEC_NBR(x) || TEST_SPEC_CHAR(x) || TEST_SPEC_W(x))
# define TEST_SPEC_NBR(x) (TEST_SIGN(x) || TEST_UNSIGN(x)  || p->spec == 'p')
# define TEST_SPEC_CHAR(x) (TEST_STR(x) || TEST_CHAR(x))
# define TEST_UNSIGN(x) (TEST_X(x) || TEST_O(x) || TEST_U(x))
# define TEST_SIGN(x) (x == 'd' || x == 'D' || x == 'i')
# define TEST_SPEC_W(x) ((x == '%' || x == 'p' ))
# define TEST_X(x) (x == 'x' || x == 'X')
# define TEST_O(x) (x == 'o' ||x == 'O')
# define TEST_U(x) (x == 'u' || x == 'U')
# define TEST_STR(x) (x == 's' || x == 'S')
# define TEST_CHAR(x) (x == 'c' || x == 'C')
# define TEST_FLAG(str, x) (test_flag(str, x) == 1)
# define TEST_2OPTS(str, x) (test_flag(str, x) == 2)

typedef struct	s_param
{
	char			spec;
	char			*flag;
	int				width;
	int				precision;
	char			*length;
	char			signe;
	int				opts_len;
	char			*value;
	int				var_len;
	int				exep;
	struct s_param	*next;
}				t_param;

uintmax_t		get_uent(va_list *ap, t_param *p);
intmax_t		get_ent(va_list *ap, t_param *p);
unsigned char	get_uchar(va_list *ap);
char			get_char(va_list *ap);
char			*parse_spec(t_param *p, va_list *ap);
int				test_flag(char *s, char c);
int				print(char *format, t_param *p);
char			*my_strjoin(char *s1, char *s2);
void			ft_putnchar(char c, int n);
char			*ft_strmap_i(char *s, int (*f)(int));
char			*ft_strndup_fr(char *str, int n);
t_param			*read_option(char *format, va_list *ap, t_param *p);
t_param			*init_tparam(char *format, va_list *ap);
void			free_tparam(t_param *p);
char			*ftp_get_value(t_param *param, va_list *ap);
char			*get_ox(t_param *p, char *tmp_val);
char			*ft_wstr(int *arr);
char			*ft_wchar(int wchar);
#endif
