/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:37 by helferna          #+#    #+#             */
/*   Updated: 2024/02/12 16:35:14 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <signal.h>
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

// typedef enum e_token_type{
// 	WORD,
// 	REDIR,
// 	PIPE
// }t_token_type;

typedef struct s_cmd {
	char *path;
	char **args;
	int	index;
	struct	s_cmd *next;
}	t_cmd;

typedef struct s_shell{
	t_cmd	*cmd;
	char	**env;
}	t_shell;

//-------------------------LEXER--------------------------//
void	tokeniser(const char *str, t_shell *s);

//-------------------------executor----------------------//
void	executor(t_shell *s);

// //------------------------BUILTINS------------------------//
int		execute_builtin(t_shell *s, int in, int out);
void	echo_cmd(t_cmd *c);
void	cd_cmd(char *path, char **env);
void	unset_cmd(char **env, char *envar);
void	pwd_cmd(char **env);
void	exit_cmd(t_shell *s);
void	env_cmd(char **env);
void	export_cmd();

//--------------------------- UTILS ---------------------------//
char	**copy_array(char **s);
void	ft_list(t_cmd *c);

//---------------------------- FREE --------------------------//
void	*free_array(char **args);
t_cmd 	*free_cmds(t_cmd *c);
void	free_shell(t_shell *s);

#endif