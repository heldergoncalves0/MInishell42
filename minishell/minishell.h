/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:10:32 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 13:39:39 by gcatarin         ###   ########.fr       */
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

#define BUFFER_SIZE 42

char	*ft_substr(char *s, size_t start, size_t len);
size_t		ft_strlen(char *s);

char	*ft_strchr(char *s, int i);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

typedef struct s_lexer{
	char 	*word;
///	char 	token;
	int 	index;
	struct s_lexer *next;
	struct s_lexer *prev;
}	t_lexer;

typedef struct s_paths
{
	char					*input;
	char					**args;
	char					**envp;
	char					*pwd;
	char					*path;
	
	struct s_simple_cmds	*simple_cmds;
	//char					*old_pwd;
	int						pipes;
	int						*pid;

}	t_paths;

char	**ft_split(char *s, char c);
size_t	ft_countword(char *s, char c);
//t_list	*ft_lstnew(void *content);

#endif 