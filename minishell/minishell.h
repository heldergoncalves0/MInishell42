/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:10:32 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 19:10:04 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h> //para readline
#include <readline/history.h>

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
	char 	*word;
	int 	token;				//0 - word //1 - token
	int 	index;
	struct s_lexer *next;
	//struct s_lexer *prev;
}	t_lex;


char	*ft_strchr(char *s, int i);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	**ft_split(char *s, char c);
size_t	ft_countword(char *s, char c);

//-------------------------LEXER--------------------------//
int		is_whitespace(char s);
int		is_quote(char s);
char	*remove_quote(char *s, int i);
void	handle_quotes(char *s);
void	tokeniser(t_paths *p, t_lex *lex_lst);
int		skip_spaces(char *s, int i);
char	*check_token(int c);

//-------------------------UTILS--------------------------//
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, size_t start, size_t len);
size_t	ft_strlen(char *s);

//-------------------------LEAVE--------------------------//
void	error_msg(char *s);
void	exitcase(t_paths *p);
void	leave(t_paths *p);

//------------------------BUILTINS------------------------//
void	built_ins(t_paths *p);

//-------------------------LISTS-------------------------//
t_lex	*ft_lstnew(int type, char *s);
int		add_token(char *token, int type, t_lex *l_lst);

#endif 