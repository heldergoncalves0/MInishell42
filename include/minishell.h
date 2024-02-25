/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:37 by helferna          #+#    #+#             */
/*   Updated: 2024/02/25 18:05:31 by gcatarin         ###   ########.fr       */
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
# include <errno.h>
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

//----------------GLOBAL FOR SIGNAL----------------------------//
extern int	g_signal;

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
	pid_t			pid;
	t_redir			*red;
	int				is_error_redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell{
	t_cmd	*cmd;
	char	**env;
	int		num_cmds;
	char	**export;
	int		status;
	int		is_exec;
}	t_shell;

//--------------------------- LEXER ----------------------------//
int		tokeniser(const char *str, t_shell *s);

//---------------------------EXPANDER---------------------------//
void	expander(t_shell *shell);
char	*expand_argument(t_shell *s, char *str, size_t j);
char	*valid_argument(char *ret);

//---------------------------- EXE -----------------------------//
void	executor(t_shell *s);
char	*find_executable_path(t_shell *s, char *binary, int i);

// //----------------------- BUILTINS --------------------------//
int		is_builtin(t_cmd *cmd, t_shell *s, int in, int out);
int		echo_cmd(t_cmd *cmd, t_shell *s, int flag, int out);
int		cd_cmd(t_cmd *cmd, t_shell *s, int in, int out);
int		unset_cmd(t_cmd *cmd, t_shell *s, int in, int out);
int		pwd_cmd(t_cmd *cmd, t_shell *s, int in, int out);
int		exit_cmd(t_cmd *cmd, t_shell *s, int in, int out);
int		env_cmd(t_cmd *cmd, t_shell *s, int in, int out);
int		export_cmd(t_cmd *cmd, t_shell *s, int in, int out);

//--------------------------- UTILS ----------------------------//
char	**copy_array(char **s);
char	**search_heredocs(t_shell *s);
char	*flag_return(int flag, char *new);
int		ft_double_strlen(char **s);
int		close_fd(int fd);
int		ft_strncmp_env(char *key, char *str);
char	*get_env(t_shell *s, char *key);
void	set_env(char **env, char *key, char *value);
char	*ft_strchr_quotes(char *s, int c);
int		ft_strint_quotes(char *s, int c);
int		ft_isquoted(char c, int flag);

//---------------------------- FREE ----------------------------//
void	*free_array(char **args);
t_cmd	*free_cmds(t_cmd *c);
void	free_shell(t_shell *s, int status);

//---------------------------- SIGNALS -------------------------//
void	set_signal_action(int sigstate);

//---------------------------- LISTS ---------------------------//
void	ft_listredir(t_redir *c);
void	ft_list(t_cmd *c);

//---------------------------- REDIR ---------------------------//
void	split_redirect(t_shell *s, int i);
void	execute_redirects(t_shell *s, t_cmd *cmd);
t_redir	*redir_compares(char **args);
int		is_redir(t_cmd *c, int i);
int		handle_infile(t_cmd *cmd, t_redir *redir);
int		handle_append(t_cmd *cmd, t_redir *redir);
void	handle_heredoc(t_shell *s, t_cmd *cmd, t_redir *redir);
int		handle_outfile(t_cmd *cmd, t_redir *redir);
char	*expand_argument(t_shell *s, char *str, size_t j);

//---------------------------- QUOTES ---------------------------//
void	handle_quotes(t_shell *shell);

//------------------------- EXPORT UTILS -------------------------//
int		ft_biggerncmp(char *s1, char *s2, int size_s1);
char	**add_var_export(char **s, char *str, int flag);
char	**overwrite_var(char **s, char *str, int flag, char *str_name);
char	*get_var_name(char *str);
int		valid_name(char *s, int in);

//----------------------------- ERROR ---------------------------//
void	invalid_name_error(t_shell *shell, char *s);
void	cmd_not_found_error(char *s);
int		invalid_file_error(char *s1, char *s2);
void	ctrl_d_error(char *s);
void	cd_error(char *s);
void	dir_error(char *s);

int		is_arg_redir(char *s);
int		sintax_verify(t_shell *shell);
int		ft_putstr_ln(char *s, int fd);
char	**sort_env(char **env_copy, int i);
int		var_exist(char **s, char *str);
int		change_outfile(int out, int cmd_out, int *fd);
void	close_fds(int fd1, int fd2);
int		cmd_error(char *str);
int		ft_ismorealnum(int str);
int		change_infile(int in, int cmd_in);
void	clean_null_expansion(t_shell *s);
t_shell *terminal(void);

#endif