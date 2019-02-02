# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 11:16:13 by ptruffau          #+#    #+#              #
#    Updated: 2018/12/03 13:37:39 by ptruffau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		21sh
GIT 		=		https://github.com/ptruffault/21sh.git
FLAG		=		-Wall -Werror -Wextra -g
OBJ_FOLDER 	= 		./bin/

FILES		=		main.c \
					signal.c \
					init_shell.c \

EXEC 		=		ft_execve.c \
					exec.c \
					redirection.c \
					bin_search.c \
					process_tools.c

EVAL			=	eval_tools.c \
					lexer.c \
					free_tools.c \
					get_instruction.c \
					token.c \
					redirect.c \
					input_missing.c \

BUILTINS		=	ft_echo.c \
					ft_cd.c \
					run_builtin.c \
					ft_env.c \
					ft_export.c \
					ft_type.c \
					ft_exit.c \
					type_tools.c

GET_INPUT	=	curs_move.c	\
				get_input.c	\
				handle_input.c	\
				history.c	\
				input_tools.c	\
				print_line.c	\
				setup.c	\
				fct.c	\
				ft_cop_pas.c	\
				ft_jump_word.c	\
				arrow_move.c	\
				ft_select.c	\
				clear_and_all.c	\
				use_termcaps.c	\
				term_settings.c\

EXPANSION		=	var.c \
					exp.c \
					curly_exp.c \
					exp_tools.c \



SRC			= 		$(addprefix "./srcs/", $(FILES)) \
					$(addprefix "./srcs/eval/", $(EVAL)) \
					$(addprefix ./srcs/builtins/, $(BUILTINS))  	\
					$(addprefix "./srcs/exec/", $(EXEC)) \
					$(addprefix "./srcs/expansion/", $(EXPANSION))	\
					$(addprefix "./srcs/get_input/", $(GET_INPUT))

OBJ			= 		$(addprefix $(OBJ_FOLDER), $(FILES:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(EVAL:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(BUILTINS:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(EXEC:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(GET_INPUT:.c=.o))	\
					$(addprefix $(OBJ_FOLDER), $(EXPANSION:.c=.o))

COLOR		= \033[01;34m
NO_COLOR	= \033[00m
OP_COLOR	= \033[1;31m
DONE 		= $(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]

all: $(NAME)

$(NAME): $(OBJ) Makefile bin
	@cp sys/.21shrc ~/.21shrc
	@make -C libft all
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@gcc  $(FLAG) $(OBJ) -I includes -Llibft -lft -ltermcap -o $(NAME)
	@printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"

bin:
	@mkdir $@

bin/%.o: srcs/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                     \r"

bin/%.o: srcs/eval/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                     \r"

bin/%.o: srcs/builtins/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                   \r"

bin/%.o: srcs/exec/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                     \r"

bin/%.o: srcs/exec/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                     \r"

bin/%.o: srcs/expansion/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                     \r"

bin/%.o: srcs/get_input/%.c
	@gcc $(FLAG) -I includes -c $< -o $@
	@printf "$(DONE) $(COLOR)$<$(NO_COLOR)                     \r"

clear:
	@clear

sclean:
	@rm -rf $(OBJ) $(NAME)

clean:
	@rm -rf $(OBJ)
	@make -C ./libft clean
fclean: clean
	rm -rf $(NAME)
	@make -C ./libft fclean

re: fclean all

fre: clear sclean all

exe: fre
	./$(NAME)

chmod:
	@sudo chmod 777 $(SRC) includes/$(NAME).h libft libft/Makefile Makefile
	@sudo make -C ./libft chmod

save: clear fclean
	@git add * srcs/* includes/*
	@git commit -m "MAKE SAVE"
	@git push
	@echo "$(DONE)"

delete_all: clear
	rm -rf *

libft:
	@echo "$(COLOR)download libft from github$(NO_COLOR)"
	@git clone https://github.com/ptruffault/libft.git

load: chmod delete_all libft
	@echo "$(COLOR)download $(NAME) from github$(NO_COLOR)"
	@git clone $(GIT) TMP 
	@make -C TMP chmod
	@mv TMP/* .
	@rm -rf TMP
