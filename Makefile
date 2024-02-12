# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:17:17 by helferna          #+#    #+#              #
#    Updated: 2024/02/11 14:56:25 by helferna         ###   ########.fr        #
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
		src/utils/utils.c

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
	make re && clear && ./minishell

# v: 
# 	make re && clear && valgrind ./minishell

v: re readline.supp
	@valgrind --show-leak-kinds=all --leak-check=full --suppressions=readline.supp  ./minishell

readline.supp:
	@wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp 2> /dev/null 1> /dev/null
.PHONY: all