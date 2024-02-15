/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:37 by helferna          #+#    #+#             */
/*   Updated: 2024/02/15 18:38:52 by gcatarin         ###   ########.fr       */
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
# include <sys/stat.h>
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
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd {
	char			*path;
	char			**args;
	int				in_file;
	int				out_file;
	int				fd[2];
	t_redir			*red;
	int				is_error_redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell{
	t_cmd	*cmd;
	char	**env;
	int		status;
}	t_shell;

//--------------------------- LEXER ----------------------------//
int		tokeniser(const char *str, t_shell *s);

//---------------------------EXPANDER---------------------------//
void	expander(t_shell *shell);

//---------------------------- EXE -----------------------------//
void	executor(t_shell *s);
char	*find_executable_path(char *binary);

// //----------------------- BUILTINS --------------------------//
int		is_builtin_execute(t_cmd *cmd, t_shell *s, int in, int out);
void	echo_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	cd_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	unset_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	pwd_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	exit_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	env_cmd(t_cmd *cmd, t_shell *s, int in, int out);
void	export_cmd(t_cmd *cmd, t_shell *s, int in, int out);

//--------------------------- UTILS ----------------------------//
char	**copy_array(char **s);
char	**search_heredocs(t_shell *s);
char	*flag_return(int flag, char *new);
int		ft_double_strlen(char **s);
void	clean_expand_cmd(t_cmd *c);
int		close_fd(int fd);
int		ft_strncmp_env(char *key, char *str);
char	*get_env(t_shell *s, char *key);
void	set_env(t_shell *s, char *key, char *value);
char	**copy_array_export(char **s, char *str, char *c);

//---------------------------- FREE ----------------------------//
void	*free_array(char **args);
t_cmd	*free_cmds(t_cmd *c);
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
int		handle_outfile(t_cmd *cmd, t_redir *redir);

#endif