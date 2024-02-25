/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:08:21 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/25 13:27:29 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(char *str, char flag)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[j])
	{
		if (flag == 0 && (str[j] == '\"' || str[j] == '\''))
			flag = str[j++];
		else if (flag == str[j] && ++j)
			flag = 0;
		else
		{
			new_str[i] = str[j];
			if (++j && !new_str[i++])
				break ;
		}
	}
	free(str);
	return (new_str);
}

void	handle_redir_quotes(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->red;
	while (redir)
	{
		if (redir->args[1] != NULL)
			redir->args[1] = remove_quotes(redir->args[1], 0);
		redir = redir->next;
	}
}

void	handle_quotes(t_shell *shell)
{
	t_cmd	*cmd;
	size_t	i;

	cmd = shell->cmd;
	while (cmd)
	{
		handle_redir_quotes(cmd);
		i = 0;
		if (cmd->args[i] != NULL)
		{
			while (cmd->args[i])
			{
				cmd->args[i] = remove_quotes(cmd->args[i], 0);
				i++;
			}
		}
		cmd = cmd->next;
	}
}
