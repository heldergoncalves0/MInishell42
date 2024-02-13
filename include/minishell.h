/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:37 by helferna          #+#    #+#             */
/*   Updated: 2024/02/13 20:22:20 by gcatarin         ###   ########.fr       */
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
# include <fcntl.h>
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

typedef enum e_redir_type{
	NONE,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND
}	t_redir_type;

typedef struct s_redir {
	char			*args[3];
	int				fd;
	t_redir_type	type;
	struct	s_redir *next;
}	t_redir;

typedef struct s_cmd {
	char 	*path;
	char 	**args;
	int		in_file;
	int		out_file;
	int		fd[2];
	t_redir	*red;
	int		is_error_redir;
	struct	s_cmd *next;
}	t_cmd;

typedef struct s_shell{
	t_cmd	*cmd;
	char	**env;
}	t_shell;

//--------------------------- LEXER ----------------------------//
int	tokeniser(const char *str, t_shell *s);

//---------------------------- EXE -----------------------------//
void	executor(t_shell *s);
char	*find_executable_path(char *binary);

// //----------------------- BUILTINS --------------------------//
int		execute_builtin(t_cmd *cmd, t_shell *s, int in, int out);
void	echo_cmd(t_cmd *c);
void	cd_cmd(char *path, char **env);
void	unset_cmd(char **env, char *envar);
void	pwd_cmd(char **env);
void	exit_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	env_cmd(char **env);
void	export_cmd();

//--------------------------- UTILS ----------------------------//
char	**copy_array(char **s);
char	**search_heredocs(t_shell *s);
char	*flag_return(int flag, char *new);
int		ft_double_strlen(char **s);

//---------------------------- FREE ----------------------------//
void	*free_array(char **args);
t_cmd 	*free_cmds(t_cmd *c);
void	free_shell(t_shell *s);

//---------------------------- SIGNALS -------------------------//
void	set_signal_action(void);

//---------------------------- LISTS ---------------------------//
void	ft_listredir(t_redir *c);
void	ft_list(t_cmd *c);

//---------------------------- REDIR ---------------------------//
void	split_redirect(t_shell *s);
int		execute_redirects(t_shell *s, t_cmd *cmd);
t_redir	*redir_compares(char **args);
int		is_redir(t_cmd *c, int i);
int		handle_infile(t_cmd *cmd, t_redir *redir);
int		handle_append(t_cmd *cmd, t_redir *redir);
void	handle_heredoc(t_shell *s, t_cmd *cmd, t_redir *redir);
 int	handle_outfile(t_cmd *cmd, t_redir *redir);
 
#endif