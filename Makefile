# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 11:16:13 by ptruffau          #+#    #+#              #
#    Updated: 2019/02/05 12:51:01 by adi-rosa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		21sh
GIT 		=		https://github.com/ptruffault/21sh.git
FLAG		=		-Wall -Werror -Wextra -g
OBJ_FOLDER 	= 		./bin/

FILES		=		main.c \
					signal.c \
					init_shell.c \
					ft_get_set.c \
					ft_free_tshell.c 

EXEC 		=		ft_execve.c \
					exec.c \
					exec_pipe.c\
					exec_file.c \
					redirection.c \
					redirect_builtins.c \
					bin_search.c \
					process_tools.c 

EVAL			=	eval_tools.c \
					tree_tools.c \
					lexer_tools.c \
					lexer.c \
					free_tools.c \
					get_instruction.c \
					heredoc_content.c\
					token.c \
					redirect.c \
					alias.c

BUILTINS		=	ft_echo.c \
					ft_cd.c \
					run_builtin.c \
					ft_env.c \
					ft_export.c \
					ft_type.c \
					ft_exit.c \
					type_tools.c \
					ft_alias.c \
					ft_jobs.c \
					check_builtins.c 

GET_INPUT	=	curs_move.c	\
				get_input.c	\
				handle_input.c	\
				history.c	\
				input_tools.c	\
				print_line.c	\
				setup.c	\
				get_history.c	\
				ft_cop_pas.c	\
				ft_jump_word.c	\
				arrow_move.c	\
				ft_select.c	\
				clear_and_all.c	\
				use_termcaps.c	\
				term_settings.c\

EXPANSION		=	exp_var.c \
					exp.c \
					expantion_tools.c \
					exp_parenth.c \
					exp_sub_parenth.c



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

$(NAME): bin $(OBJ) Makefile 
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

save:
	git add -A && git commit -m "make save" && git push