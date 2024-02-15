/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:31 by helferna          #+#    #+#             */
/*   Updated: 2024/02/15 15:39:27 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_shell *shell)
{
	int		i;
	char	*env_value;
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
	while (cmd)
	{
		while (cmd->args[i] != NULL)
		{
			if (cmd->args[i][0] == '$')
			{
				env_value = get_env(shell, cmd->args[i] + 1);
				free(cmd->args[i]);
				if (ft_strlen(env_value) != 0)
					cmd->args[i] = ft_strdup(env_value);
				else
					cmd->args[i] = "\2";
			}
			i++;
		}
		clean_expand_cmd(cmd);
		cmd = cmd->next;
	}
}
// echo ${PWD/atacu}
