/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:21:25 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/24 19:34:40 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*redir_struct(char *name, char *file, t_redir_type type)
{
	t_redir	*redir_ptr;

	redir_ptr = ft_calloc(sizeof(t_redir), 1);
	redir_ptr->args[0] = name;
	redir_ptr->args[1] = file;
	redir_ptr->type = type;
	return (redir_ptr);
}

t_redir	*redir_compares(char **args)
{
	if (ft_strncmp(args[0], ">", 2) == 0)
		return (redir_struct(args[0], args[1], OUTFILE));
	else if (ft_strncmp(args[0], "<", 2) == 0)
		return (redir_struct(args[0], args[1], INFILE));
	else if (ft_strncmp(args[0], "<<", 3) == 0)
		return (redir_struct(args[0], args[1], HEREDOC));
	else if (ft_strncmp(args[0], ">>", 3) == 0)
		return (redir_struct(args[0], args[1], APPEND));
	return (NULL);
}

void	clean_redir_cmd(t_cmd *c)
{
	size_t	i;
	size_t	j;
	int		flag;

	j = 0;
	i = -1;
	flag = 0;
	while (c->args[++i])
	{
		flag = is_redir(c, i);
		if (flag)
		{
			j = i;
			c->args[i++] = 0;
			while (c->args[++i])
			{
				c->args[j++] = c->args[i];
				c->args[i] = 0;
			}
			c->args[j] = 0;
			clean_redir_cmd(c);
			break ;
		}
	}
}

void	split_redirect(t_shell *s, int i)
{
	t_redir	*redir;
	t_redir	*end;
	t_cmd	*cmd;

	end = NULL;
	cmd = s->cmd;
	while (cmd)
	{
		i = -1;
		while (cmd->args[++i])
		{
			redir = redir_compares(&cmd->args[i]);
			if (redir && *cmd->args[i] != '\0')
			{
				if (!cmd->red)
					cmd->red = redir;
				else if (end)
					end->next = redir;
				end = redir;
				i += (*cmd->args[i + 1] != '\0');
			}
		}
		clean_redir_cmd(cmd);
		cmd = cmd->next;
	}
}

void	execute_redirects(t_shell *s, t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->red;
		while (redir && cmd->is_error_redir == 0)
		{
			if (redir->args[1][0] == '$')
				cmd->is_error_redir++;
			if (redir->type == APPEND && handle_append(cmd, redir) == 0)
				invalid_file_error(strerror(errno), redir->args[1]);
			else if (redir->type == INFILE && handle_infile(cmd, redir) == 0)
				invalid_file_error(strerror(errno), redir->args[1]);
			else if (redir->type == OUTFILE && handle_outfile(cmd, redir) == 0)
				invalid_file_error(strerror(errno), redir->args[1]);
			else if (redir->type == HEREDOC)
				handle_heredoc(s, cmd, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

// << ola << oi << lol << final cat
// << EOF cat
// c=c a=a t=t   depois->	$c$b$c src/main.c

// echo ola |			=> testar com | "" e isso 
// | echo ola			echo gui | | echo gui
// resolver no syntax verify
// $sdfksd echo gui
// 
// cat Makefile | grep pr | head -n 5 | hello	=> exit code 127
// cat Makefile | grep pr | head -n 5 | cat ola	=> parte a shell (suposto)
// cat < test # with non-existent test
// cat > gui$lherme
// export var ="cat Makefile | grep >"
// c$var Makefile # with var=at
// minishell
// ctrl-C . 130 sur bin(ex : sleep 10)&line vide
// ctrl-\ .131 sur bin
// cat < Makefile | grep gcc > output