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

FLAG		=	-Wall -Werror -Wextra -g

FILES		=		main.c \
					signal.c \
					correct_input.c \
					disp.c\
					exec.c \
					exec_redirect.c \

SYS 		=		fd.c \
					ft_execve.c


EVAL			=	get_bin_path.c \
					eval_tools.c \
					get_instruction.c \
					token.c

BUILTINS		=	ft_echo.c \
					ft_cd.c \
					run_builtin.c \
					ft_env.c
FILE_FOLDER		= 	./srcs/
EVAL_FOLDER	= 	./srcs/eval/
BUILTINS_FOLDER	=	./srcs/builtins/

OBJ_FOLDER 	= 		./bin/
SRC			= 		$(addprefix $(FILE_FOLDER), $(FILES)) \
					$(addprefix $(EVAL_FOLDER), $(EVAL)) \
					$(addprefix $(BUILTINS_FOLDER), $(BUILTINS))  	\
					$(addprefix $(SYS_FOLDER), $(SYS))
OBJ			= 		$(addprefix $(OBJ_FOLDER), $(FILES:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(EVAL:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(BUILTINS:.c=.o)) \
					$(addprefix $(OBJ_FOLDER), $(SYS:.c=.o))

COLOR		= \033[01;34m
NO_COLOR	= \033[00m
OP_COLOR	= \033[1;31m
DONE 		= $(NO_COLOR)[\033[1;32mOK$(NO_COLOR)]

all: $(NAME)

$(NAME): $(OBJ) Makefile bin
	@make -C libft all
	@echo "$(OP_COLOR) building $(NAME)$(NO_COLOR)"
	@gcc $(OBJ) -I includes -Llibft -lft -ltermcap -o $(NAME)
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

bin/%.o: srcs/sys/%.c 
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
	@sudo chmod 777 $(SRC) includes/$(NAME).h libft libft/Makefile
	@sudo make -C ./libft chmod

save: clear fclean
	@git add * srcs/* includes/*
	@git commit -m  "make save"
	@git push
	@echo "$(DONE)"

delete_all: clear
	rm -rf *

libft:
	@echo "$(COLOR)download libft from github$(NO_COLOR)"
	@git clone https://github.com/ptruffault/libft.git

load: delete_all libft
	@echo "$(COLOR)download $(NAME) from github$(NO_COLOR)"
	@git clone $(GIT) TMP && mv TMP/* . && rm -rf TMP 
