/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:25:04 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 18:56:47 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_cmd *cmd, t_redir *redir)
{
	redir->fd = open(redir->args[1], O_APPEND | O_CREAT | O_RDWR, 0644);
	if (redir->fd == -1)
		return (0);
	if (cmd->out_file != -1)
		close(cmd->out_file);
	cmd->out_file = redir->fd;
	return (1);
}
int	handle_outfile(t_cmd *cmd, t_redir *redir)
{
	redir->fd = open(redir->args[1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (redir->fd == -1)
		return (0);
	if (cmd->out_file != -1)
		close(cmd->out_file);
	cmd->out_file = redir->fd;
	return (1);
}
