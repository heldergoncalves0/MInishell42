/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:25:04 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 20:15:16 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_file(t_redir *redir)
{
	static struct stat	info;

	if (lstat(redir->args[1], &info) == 0)
		return (1);
	return (0);
}

void	verify_files(t_cmd *cmd, t_redir *redir)
{
	while (redir && cmd->is_error_redir == 0)
	{
		if (verify_file(redir) == 0)
		{
			cmd->is_error_redir++;
			invalid_file_error(strerror(errno), redir->args[1]);
		}
		redir = redir->next;
	}
}

int	handle_append(t_cmd *cmd, t_redir *redir)
{
	struct stat	info;

	if (stat(redir->args[1], &info) == 0)
	{
		if (errno == ENOENT)
		{
			redir->fd = open(redir->args[1], O_APPEND | O_CREAT | O_WRONLY, 0644);
			if (redir->fd == -1 && ++cmd->is_error_redir)
				return (0);
		}
		else
		{
			redir->fd = open(redir->args[1], O_APPEND | O_WRONLY, 0644);
			if (redir->fd == -1 && ++cmd->is_error_redir)
				return (0);
		}
		close_fd(cmd->out_file);
		cmd->out_file = redir->fd; 
		return (1);
	}
	++cmd->is_error_redir;
	return (0);
}

int	handle_outfile(t_cmd *cmd, t_redir *redir)
{
	struct stat	info;

	if (stat(redir->args[1], &info) == 0)
	{
		if (errno == ENOENT)
		{
			redir->fd = open(redir->args[1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (redir->fd == -1 && ++cmd->is_error_redir)
				return (0);
		}
		else
		{
			redir->fd = open(redir->args[1], O_TRUNC | O_WRONLY, 0644);
			if (redir->fd == -1 && ++cmd->is_error_redir)
				return (0);
		}
		close_fd(cmd->out_file);
		cmd->out_file = redir->fd;
		return (1);
	}
	++cmd->is_error_redir;
	return (0);
}

int	handle_infile(t_cmd *cmd, t_redir *redir)
{
	struct stat	info;

	if (stat(redir->args[1], &info) == 0)
	{
		redir->fd = open(redir->args[1], O_RDONLY, 0644);
		if (redir->fd == -1 && ++cmd->is_error_redir)
			return (0);
		close_fd(cmd->in_file);
		cmd->in_file = redir->fd;
		return (1);
	}
	else
	{
		++cmd->is_error_redir;
		return (0);
	}
}
