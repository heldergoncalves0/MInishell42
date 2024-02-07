/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:37 by helferna          #+#    #+#             */
/*   Updated: 2024/02/07 12:58:10 by helferna         ###   ########.fr       */
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

typedef struct s_mini{
	char **cmd_paths;
	char *path;
}	t_mini;

typedef struct s_paths
{
	char					*input;
	char					*args;
	char					**envp;
	char					*pwd;
	char					*path;
	char					**paths;
	char					*old_pwd;
	char					*prompt;		//
	struct s_lex			*lex_lst;
	
	//struct s_simple_cmds	*simple_cmds;
}	t_paths;

typedef struct s_lex{
	char	*word;
	int		token;				//0 - word //1 - token
	int		index;
	struct	s_lexer *next;
	//struct s_lexer *prev;
}	t_lex;

//executor
int		executor(char **env, t_mini *mini);
void	exec_builtin(char **cmd, t_mini *mini, char **env);
void	cd(t_mini *mini, char *path, char **env);
void	unset(t_mini	*mini, char **env, char *envar);
void	pwd(char **envp);

//-------------------------LEXER--------------------------//
int		is_whitespace(char s);
int		is_quote(char s);
char	*remove_quote(char *s, int i);
void	handle_quotes(char *s);
void	tokeniser(t_paths *p, t_lex *lex_lst);
int		skip_spaces(char *s, int i);
char	*check_token(int c);

//-------------------------LEAVE--------------------------//
void	error_msg(char *s);
void	exitcase(t_paths *p);
void	leave(t_paths *p);

//------------------------BUILTINS------------------------//
void	built_ins(t_paths *p);

//-------------------------LISTS-------------------------//
t_lex	*ft_newlst(int type, char *s);
int		add_token(char *token, int type, t_lex *l_lst);
void	printLinkedList(t_lex *head);

#endif