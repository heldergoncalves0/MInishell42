/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:25:04 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 21:12:45 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_cmd *cmd, t_redir *redir)
{
	struct stat	info;

	if (stat(redir->args[1], &info) == 0 || cmd->is_error_redir)
	{
		redir->fd = open(redir->args[1], O_APPEND | O_WRONLY, 0644);
		if (redir->fd == -1 && ++cmd->is_error_redir)
			return (0);
		close_fd(cmd->out_file);
		cmd->out_file = redir->fd; 
		return (1);
	}
	else if (errno == ENOENT)
	{
		redir->fd = open(redir->args[1], O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (redir->fd == -1 && ++cmd->is_error_redir)
			return (0);
		close_fd(cmd->out_file);
		cmd->out_file = redir->fd; 
		return (1);
	}
	else
	{
		++cmd->is_error_redir;
		return (0);
	}
}

int	handle_outfile(t_cmd *cmd, t_redir *redir)
{
	struct stat	info;

	if (stat(redir->args[1], &info) == 0 || cmd->is_error_redir)
	{
		redir->fd = open(redir->args[1], O_TRUNC | O_WRONLY, 0644);
		if (redir->fd == -1 && ++cmd->is_error_redir)
			return (0);
		close_fd(cmd->out_file);
		cmd->out_file = redir->fd;
		return (1);
	}
	else if (errno == ENOENT)
	{
		redir->fd = open(redir->args[1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (redir->fd == -1 && ++cmd->is_error_redir)
			return (0);
		close_fd(cmd->out_file);
		cmd->out_file = redir->fd;
		return (1);
	}
	else
	{
		++cmd->is_error_redir;
		return (0);
	}
}

int	handle_infile(t_cmd *cmd, t_redir *redir)
{
	struct stat	info;

	if (stat(redir->args[1], &info) == 0 || cmd->is_error_redir)
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
