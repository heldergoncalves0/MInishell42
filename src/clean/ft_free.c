/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 17:11:48 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_array(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		free(args[i++]);
	}
	free(args);
	return (NULL);
}

t_redir	*free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (redir)
	{
		tmp = redir->next;
		free_array(redir->args);
		redir = tmp;
	}
	return (NULL);
}

t_cmd	*free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd->next;
		free_redirs(cmd->red);
		cmd->args = free_array(cmd->args);
		free(cmd->path);
		free(cmd);
		cmd = tmp;
	}
	return (NULL);
}

void	free_shell(t_shell *s, int status)
{
	clear_history();
	free_cmds(s->cmd);
	free_array(s->env);
	free_array(s->export);
	exit(status);
}
