/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:25:04 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/20 16:24:53 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append(t_cmd *cmd, t_redir *redir)
{
	//access para ver se existe, se existe ver se tenho permissoes para escrever com o stat()
	//se nao existe crio sem permissoes, e se existe faco open com o_wonly e o o_append
	redir->fd = open(redir->args[1], O_APPEND | O_CREAT | O_RDWR, 0644);
	if (redir->fd == -1 && ++cmd->is_error_redir)
		return (0);
	close_fd(cmd->out_file);
	cmd->out_file = redir->fd; 
	return (1);
}

int	handle_outfile(t_cmd *cmd, t_redir *redir)
{
	// if (!access(redir->args[1]))
	//access para ver se existe, se existe ver se tenho permissoes para escrever com o stat()
	//se nao existe crio, e se existe faco open com o_trunc e o_wonly
	
	redir->fd = open(redir->args[1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (redir->fd == -1 && ++cmd->is_error_redir)
		return (0);
	close_fd(cmd->out_file);
	cmd->out_file = redir->fd;
	return (1);
}
