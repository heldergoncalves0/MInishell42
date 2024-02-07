/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:37 by helferna          #+#    #+#             */
/*   Updated: 2024/02/07 21:47:48 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>

//colors
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RES "\e[0;0m"

//useless defines
# define BUILTIN_COUNT 7

typedef enum e_token_type{
	WORD,
	REDIR,
	PIPE
}t_token_type;

// typedef struct s_mini{
// 	char **cmd_paths;
// 	char *path;
// }	t_mini;

typedef struct s_cmd {
	char *path;
	char **args;
	struct	s_cmd *next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd *cmd;
	
}	t_shell;

// //-------------------------LEXER--------------------------//
void	tokeniser(const char *str, t_shell *p);


// //-------------------------executor----------------------//
// int		executor(char **env, t_mini *mini);
// void	exec_builtin(char **cmd, t_mini *mini, char **env);
// void	cd(t_mini *mini, char *path, char **env);
// void	unset(t_mini	*mini, char **env, char *envar);
// void	pwd(char **envp);

// //-------------------------LEXER--------------------------//
// int		is_whitespace(char s);
// int		is_quote(char s);
// char	*remove_quote(char *s, int i);
// void	handle_quotes(char *s);
// void	tokeniser(t_paths *p);
// int		skip_spaces(char *s, int i);
// char	*check_token(int c);

//-------------------------LEAVE--------------------------//
void	exitcase(t_shell *p, char *s);
void	leave(t_shell *p);

// //------------------------BUILTINS------------------------//
// void	built_ins(t_paths *p);

// //-------------------------LISTS-------------------------//
// t_lex	*ft_lexnew(t_token_type type, char *s);
// int		add_token(char *token, t_token_type type, t_lex **l_lst);
// t_lex	*ft_lexlast(t_lex *lst);
// void	ft_showelement(t_lex *l_lst);

// char	*check_token_extra(int c);

#endif