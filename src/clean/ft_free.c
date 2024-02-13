/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 20:41:22 by gcatarin         ###   ########.fr       */
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
	int		i;

	i = 0;
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
	int		i;

	i = 0;
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

void	free_shell(t_shell *s)
{
	clear_history();
	free_cmds(s->cmd);
	free_array(s->env);
	ft_putstr_fd("exit\n", 2);
	exit(s->status);
}
