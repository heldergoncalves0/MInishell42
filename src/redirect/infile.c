/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:42:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/20 16:20:09 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(t_cmd *cmd, t_redir *redir)
{
	//se nao existe, erro
	//se existe abro sem permissoes
	redir->fd = open(redir->args[1], O_RDONLY);
	if (redir->fd == -1 && ++cmd->is_error_redir)
		return (0);
	close_fd(cmd->in_file);
	cmd->in_file = redir->fd;
	return (1);
}
