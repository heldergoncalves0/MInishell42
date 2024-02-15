/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:31 by helferna          #+#    #+#             */
/*   Updated: 2024/02/15 13:26:49 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_shell *shell)
{
	int		i;
	char 	*env_value;
	t_cmd	*cmd;

    cmd = shell->cmd;
	i = 0;
	while(cmd)
	{
		while (cmd->args[i] != NULL)
		{
			if (cmd->args[i][0] == '$')
			{
				env_value = get_env(shell, cmd->args[i] + 1);
				free(cmd->args[i]);
				cmd->args[i] = ft_strdup(env_value);
			}
			i++;
		}
		cmd = cmd->next;
	}
}
