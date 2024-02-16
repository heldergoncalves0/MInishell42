# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:17:17 by helferna          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/02/16 17:25:14 by helferna         ###   ########.fr        #
=======
#    Updated: 2024/02/16 17:36:22 by gcatarin         ###   ########.fr        #
>>>>>>> parser
#                                                                              #
# **************************************************************************** #

NAME  = minishell
OS    = $(shell uname)
CC    = @cc
FLAGS = -Wall -Wextra -g -lreadline -fsanitize=address
LFT   = libft/libft.a
INC   = -I./libft -I./include
SRC   = src/main.c src/parser/lexer.c src/clean/ft_free.c src/executor/executor.c \
		src/builtins/exec_builtin.c src/builtins/echo.c src/builtins/cd.c src/builtins/unset.c \
		src/builtins/env.c src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c \
		src/utils/ft_utils.c src/signals/signals.c src/redirect/heredoc.c src/utils/ft_lists.c \
		src/redirect/redirect.c src/redirect/infile.c src/redirect/outfile.c src/expander/expander.c \
		src/utils/ft_utils_extra.c src/parser/quotes.c

OBJ   = $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(MLX) $(LFT) obj $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I./include -o $@ $^ $(LFT)

$(LFT):
	@make -sC libft

obj:
	@mkdir -p obj

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@
	@mkdir -p obj

clean:
	@make -sC libft clean
	@rm -rf $(OBJ) obj

fclean: clean
	@make -sC libft fclean
	@rm -rf $(NAME)

re: fclean all

r: 
	@make re && clear && ./minishell

# v: 
# 	make re && clear && valgrind ./minishell

v: re readline.supp
	clear
	@valgrind  --track-fds=yes --show-leak-kinds=all --leak-check=full --suppressions=readline.supp  ./minishell

readline.supp:
	@wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp 2> /dev/null 1> /dev/null
.PHONY: all
