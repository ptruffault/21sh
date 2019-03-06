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
					ft_free_tshell.c \
					init_envv.c

EXEC 		=		ft_execve.c \
					exec.c \
					exec_pipe.c\
					execve_pipe.c \
					exec_file.c \
					redirection.c \
					redirect_builtins.c \
					bin_search.c \
					process_tools.c \
					init_process.c

EVAL		=		eval_tools.c \
					tree_tools.c \
					lexer_tools.c \
					lexer.c \
					free_tools.c \
					get_instruction.c \
					heredoc_content.c\
					token.c \
					redirect.c \
					alias.c \
					t_word_tools.c \

BUILTINS	=		ft_echo.c \
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

GET_INPUT	=		curs_move.c	\
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
					term_settings.c \
					ft_jump_line.c	\

EXPANSION	=		exp_var.c \
					exp.c \
					expantion_tools.c \
					exp_parenth.c \
					exp_sub_parenth.c \
					cut_string.c\
					parenth_tools.c



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

COLOR		= 		\033[01;34m
NO_COLOR	= 		\033[00m
OP_COLOR	= 		\033[1;31m
DONE 		= 		$(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]
KO			= 		$(NO_COLOR)[\033[00;31mKO$(NO_COLOR)]

all: $(NAME)

bin:
	@mkdir $@

$(NAME): bin $(OBJ) Makefile
	@make -C libft all
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@gcc  $(FLAG) $(OBJ) -I includes -Llibft -lft -ltermcap -o $(NAME)
	@printf "$(DONE)$(OP_COLOR)$(NAME)$(NO_COLOR)  \n"


bin/%.o: srcs/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"


bin/%.o: srcs/eval/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"

bin/%.o: srcs/builtins/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"

bin/%.o: srcs/exec/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"

bin/%.o: srcs/exec/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"

bin/%.o: srcs/expansion/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"

bin/%.o: srcs/get_input/%.c
	@printf "$(COLOR)$<$(NO_COLOR) -> "
	@touch $<
	@gcc $(FLAG) -I includes -c $< -o $@ && printf "$(DONE)\n" || printf "$(KO)\n"

clear:
	@clear

sclean:
	@rm -rf $(OBJ) $(NAME)

clean:
	@rm -rf bin
	@make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	@make -C ./libft fclean

re: fclean all

fre: clear sclean all

exe: fre
	./$(NAME)

val: all
	@valgrind --leak-check=full -v ./$(NAME)

save: fclean clear
	@git add -A && git commit -m "make save" && git push \
	&& printf "$(COLOR)save$(NO_COLOR) : $(DONE)\n" || printf"$(OP_COLOR)save : KO\n$(NO_COLOR)"

.PHONY: clear sclean clean fclean save
