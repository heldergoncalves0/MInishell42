/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:31 by helferna          #+#    #+#             */
/*   Updated: 2024/02/16 12:09:31 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*valid_argument(t_shell *shell, char *str)
// {
// 	int	i;
// 	char *ret;

// 	ret = str;
// 	i = 0;
// 	while (ret[i])
// 	{
// 		if (!ft_isalnum(ret[i]))
// 		{
// 			ret[i] = '\0';
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (ret);
// }

// static char	*get_env_ret(t_shell *s, char *ret)
// {
// 	char	*env_value;

// 	env_value = get_env(s, ret);
// 	if (ft_strlen(env_value) != 0)
// 	{
// 		// ft_putstr_fd("env_value: ", 2);
// 		// ft_putstr_ln(env_value, 2);
// 		return (ft_strdup(env_value));
// 	}
// 	return (ft_strdup("nada"));
// }

// // static char	*check_expand(t_shell *s, t_cmd *cmd)
// // {
// // 	size_t	i;
// // 	size_t	j;
// // 	char	*arg;
// // 	char	*tmp;

// // 	i = 0;
// // 	j = 0;
// // 	arg = NULL;
// // 	tmp = NULL;
// // 	while (cmd->args[i])
// // 	{
// // 		j = 0;
// // 		while (cmd->args[i][j])
// // 		{
// // 			if (cmd->args[i][j] == '$')
// // 			{
// // 				arg = valid_argument(s, ++cmd->args[i]);
// // 				get_key();
// // 				ft_putstr_fd("ARG: ", 2);
// // 				ft_putstr_ln(arg, 2);
// // 				// cmd->args[i] = ft_strjoin(get_env_ret(s, arg), cmd->args[i]);
// // 				check_expand(s, cmd);
// // 			}
// // 			tmp[]
// // 			j++;
// // 		}
// // 		i++;
// // 	}
// }

// void	expander(t_shell *shell)
// {
// 	size_t		i;
// 	t_cmd	*cmd;

// 	cmd = shell->cmd;
// 	i = 0;
// 	while (cmd)
// 	{
// 		if (cmd->args[i] != NULL)	
// 		{
// 			// cmd->args[i] = 
// 			// ft_putstr_ln(cmd->args[i], 2);
// 			check_expand(shell, cmd);
// 			i++;
// 		}
// 		// clean_expand_cmd(cmd);
// 		cmd = cmd->next;
// 	}
// }
// echo ${PWD/atacu}
// >|cat
// CAT << "$USER



// $user/awdawdawd/dwdad$user/asas