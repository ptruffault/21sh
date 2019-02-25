NAME		=	libft.a

GIT 		= https://github.com/ptruffault/libft.git

FILES = ft_memset.c ft_strncut.c ft_bzero.c ft_strnew_nchar.c \
ft_memcpy.c ft_memmove.c ft_memccpy.c ft_strchr.c ft_close.c\
ft_memchr.c ft_memcmp.c  ft_strcpy.c ft_strdup.c ft_putchar_color.c\
ft_strlen.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_isequal.c\
ft_strlcat.c ft_strrchr.c ft_strstr.c  ft_strnstr.c ft_match.c\
ft_strcmp.c  ft_strncmp.c ft_atoi.c ft_ismin.c ft_strdel_from_arr.c \
ft_ismaj.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_search_line_in_file.c\
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c get_next_line.c\
ft_memalloc.c ft_itoa.c  ft_putchar_fd.c ft_memdel.c ft_strdel.c\
ft_putchar.c ft_putendl_fd.c ft_putendl.c ft_putnbr_fd.c \
ft_putnbr.c ft_putstr_fd.c ft_putstr.c ft_putstrarr.c ft_write_in_file.c\
ft_strclr.c ft_strequ.c ft_striter.c ft_search_tfile.c ft_get_prev_path.c \
ft_striteri.c ft_strjoin.c ft_strmap.c ft_strmapi.c ft_strpull.c ft_open.c\
ft_strnequ.c ft_strnew.c ft_strsplit.c ft_strsub.c ft_get_line_in_file.c\
ft_strtrim.c ft_strsplit_word.c ft_isspace.c ft_count_word.c ft_delchar_n.c \
ft_sqrt.c ft_strarrlen.c ft_strarrjoin.c ft_isempty.c ft_strchr_end.c\
ft_realloc.c  ft_new_path.c ft_get_tfile.c ft_error.c ft_strndup.c\
ft_get_file_inf.c  ft_free_tfile.c ft_new_tfile.c ft_itoa_base_uintmax.c \
ft_putstr_color_fd.c ft_sort_tfile.c ft_freestrarr.c ft_get_next_word.c\
ft_str_startwith.c ft_strsplit_whitespace.c ft_char_to_str.c ft_get_txt.c\
ft_itoa_base_intmax.c ft_stradd_char.c ft_strjoin_fr.c ft_putnstr.c 


FT_PRINTF  = 	get_val.c \
				ft_printf.c \
				param.c \
				get_tmpval.c \
				disp.c \
				wchar_utils.c \
				fun_tools.c \
				get_ox.c \
				get_type.c \
				tools_tparam.c

TENVV 		=	init_tenvv.c \
				ft_get_set_envv.c \
				tenvv_tools.c \
				tenvv_tools_2.c  \
				tenvv_to_tab.c \
				ft_setenv.c \
				ft_unsetenv.c 

FLAG		 = -Wall -Werror -Wextra -g

FILE_FOLDER	= ./srcs/
GET_INPT_FO = ./srcs/get_input/
TENVV_FO	= ./srcs/tenvv/
FT_PRINTF_FO = ./srcs/ft_printf/
OBJ_FOLDER 	= ./bin/
SRC			= $(addprefix $(FILE_FOLDER), $(FILES)) \
			$(addprefix $(TENVV_FO), $(TENVV)) \
			$(addprefix $(FT_PRINTF_FO), $(FT_PRINTF)) 
OBJ			= $(addprefix $(OBJ_FOLDER), $(FILES:.c=.o)) \
			$(addprefix $(OBJ_FOLDER), $(TENVV:.c=.o)) \
			$(addprefix $(OBJ_FOLDER), $(FT_PRINTF:.c=.o))

COLOR		= \033[01;34m
NO_COLOR	= \033[00m
OP_COLOR	= \033[1;31m
DONE 		= $(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]


all:  Makefile bin srcs auteur $(NAME)

$(NAME): $(OBJ) 
	@ar rc $@ $^
	@ranlib $@
	@printf "\n$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

auteur:
	@echo "ptruffau" > auteur

bin:
	@mkdir $@

srcs:
	@mkdir $@

bin/%.o: $(FILE_FOLDER)%.c 
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "libft$(NO_COLOR)  $(DONE) $(COLOR)$<$(NO_COLOR)                               \r"

bin/%.o: $(TENVV_FO)%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "tenvv$(NO_COLOR)  $(DONE) $(COLOR)$<$(NO_COLOR)                               \r"

bin/%.o: $(FT_PRINTF_FO)%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "ft_printf$(NO_COLOR)  $(DONE) $(COLOR)$<$(NO_COLOR)                               \r"

clean:
	@rm -rf bin/*
	@echo "$(OP_COLOR)Cleaning (libft/*.o)\t $(DONE)"

fclean: clean
	@echo "$(OP_COLOR)Cleaning (libft/libft.a) $(DONE)"
	@rm -rf $(NAME)

re: fclean all

chmod:
	@chmod 777 *
	@chmod 777 srcs/*
	@chmod 777 srcs/tenvv/*
	@chmod 777 srcs/ft_printf/*
	@chmod 777 includes/*

save: clean fclean
	@git add * $(SRCS)
	@git commit -m "[make save]"
	@git push
	@echo "\t$(DONE)"

update:
	@echo "download lastest $(NAME) version"
	@clear && rm -rf * && git clone $(GIT) tmpfold
	@mv tmpfold/* . && rm -rf tmpfold

.PHONY: all clean fclean re chmod save update


































