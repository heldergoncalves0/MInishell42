# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:17:17 by helferna          #+#    #+#              #
#    Updated: 2024/02/07 21:53:29 by gcatarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell
OS    = $(shell uname)
CC    = @cc
FLAGS = -Wall -Wextra -g -lreadline #-fsanitize=address
LFT   = libft/libft.a
INC   = -I./libft
SRC   = src/main.c src/parser/lexer.c src/clean/ft_free.c
#  src/executor/executor.c src/builtins/exec_builtin.c src/builtins/cd.c src/builtins/unset.c \
# 		src/builtins/pwd.c src/parser/lexer_utils.c src/parser/ft_quotes.c \
# 		 src/lst/ft_lists.c src/lst/ft_lists_extra.c
OBJ   = $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(MLX) $(LFT) obj $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ $(LFT)

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

v: 
	make re && clear && valgrind ./minishell

.PHONY: all