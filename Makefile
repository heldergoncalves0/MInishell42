# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:17:17 by helferna          #+#    #+#              #
#    Updated: 2024/02/07 11:52:53 by helferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell
OS    = $(shell uname)
CC    = @cc
FLAGS = -Wall -Wextra -g -fsanitize=address -lreadline
LFT   = libft/libft.a
INC   = -I./libft
SRC   = src/main.c src/executor/executor.c src/builtins/exec_builtin.c src/builtins/cd.c src/builtins/unset.c \
		src/builtins/pwd.c src/parser/lexer.c src/parser/lexer_utils.c src/parser/ft_quotes.c \
		src/clean/ft_free.c src/lst/lst.c
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

.PHONY: all