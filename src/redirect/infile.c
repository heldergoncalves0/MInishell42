/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:42:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 20:56:16 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(t_cmd *cmd, t_redir *redir)
{
	redir->fd = open(redir->args[1], O_RDONLY , 0644);
	if (redir->fd == -1 && ++cmd->is_error_redir)
		return (0);
	close_fd(cmd->in_file);
	cmd->in_file = redir->fd;
	return (1);
}

