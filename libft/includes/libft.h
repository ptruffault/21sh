/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:16:01 by ptruffau          #+#    #+#             */
/*   Updated: 2019/02/08 14:52:37 by adi-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <stdint.h>
# include "tenvv.h"
# define BUFF_SIZE 256

# define BLEUCLAIR 	"\033[01;34m"
# define ROUGE 		"\033[00;31m"
# define BLEU 		"\033[00;34m"
# define SOULIGNE 	"\033[04m"
# define NORMAL 	"\033[00m"
# define VERT  		"\033[1;32m"
# define CYAN 		"\033[1;36m"
# define MAGENTA 	"\033[1;35m"
# define JAUNE		"\033[1;39m"

typedef enum	e_boolen {
	FALSE = 0,
	TRUE = 1
}				t_bool;

typedef struct s_file	t_file;
struct	s_file
{
	char		*name;
	char		*path;
	char		type;
	char		*mode;
	int			nb_of_l;
	char		*owner;
	char		*group;
	int			size;
	time_t		modif_time;
	time_t		access_time;
	int			block;
	char		*link;
	int			total;
	t_file		*sdir;
	t_file		*next;
};

int		ft_printf(char *format, ...);
char	*ft_strchr_end(const char *src, char c);
int		ft_close(int fd);
int		ft_count_word(char *s);
char	**ft_strarrjoin(char **src, char **to_add);
char	**ft_strarrjoin_fr(char **src, char **to_add);
int		ft_match(char *s1, char *s2);
void	ft_write_in_file(char *path, char *str);
char	*ft_get_line_in_file(char *path, int n);
int		ft_open(char *path);
char	*ft_search_line_in_file(char *path, char *src);
void	ft_putstrarr_fd(char **t, int fd);
void	ft_strdel_from_arr(int n, void *arr, size_t width, int len);
char	*ft_get_next_word(char *str);
void	ft_putchar_color(char c, char *color);
void	ft_putchar_color_fd(char c, char *color, int fd);
size_t	ft_strarrlen(char **arr);
char	**ft_strsplit_word(char *str);
void	warning(char *descript, char *opts);
void	error(char *descript, char *opts);
void	warning_c(char *descript, char opts);
void	error_c(char *descript, char opts);
void	error_i(char *descrpt, int i);
char	*ft_char_to_str(char c);
char	*ft_itoa_base(intmax_t value, int base);
char	*ft_itoa_base_u(uintmax_t value, int base);
char	*ft_strjoin_fr(char *s1, char *s2);
char	*ft_stradd_char(char *str, char c);
char	*ft_strnew_nchar(char c, int n);
char	*ft_strjoin_fr(char *s1, char *s2);
void	ft_get_file_inf(t_file *file, struct dirent *t_dir, char *path);
t_file	*ft_get_tfile(char *path, int recursive);
t_file	*ft_search_tfile(char *path, int recursif);
void	ft_put_tfile(t_file *file);
t_file	*ft_new_tfile(void);
void	ft_del_tfile(t_file *file);
void	ft_free_tfile(t_file *file);
void	ft_putnstr(char *str, int n);
t_file	*ft_dir_compltion(char *str);
t_file	*ft_sort_tfile(t_file *file, int (*f)(t_file *file, t_file *tmp));
char	*ft_new_path(char *s1, char *s2);
char	*ft_get_prev_path(char *path);
int		get_next_line(const int fd, char **line);
int		ft_strcmp_castless(char *s1, char *s2);
char	**ft_freestrarr(char **arr);
void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size);
int		ft_str_startwith(char *s1, char *s2);
int		ft_str_endwith(char *s1, char *s2);
char	**ft_get_txt(int fd);
char	**ft_strsplit_whitespace(char *s);
char	*ft_strpull(char *src, char *ptr, int len, char *value);
char	*ft_strndup(char *src, int len);
char	**ft_strsplit(char const *s, char c);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isblank(int c);
void	ft_bzero (void *s, size_t n);
char	*ft_strtrim(char const *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy (void *s1, const void *s2, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *s1, const char *s2);
char	*ft_delchar_n(char *s, int n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_ismaj(char c);
int		ft_ismin(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isequal(char *s);
int		ft_isempty(char *s);
int		ft_isspace(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(char const *s);
char	**ft_strsplit(char const *s, char c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putstr_color(char *str, char *color);
void	ft_putstr_color_fd(char *str, char *color, int fd);
void	ft_putstrarr(char **t);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
