/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:31 by helferna          #+#    #+#             */
/*   Updated: 2024/02/15 20:38:51 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*get_env_ret(t_shell *shell, char *ret)
{
	char	*env_value;

	env_value = get_env(shell, ret);
	if (ft_strlen(env_value) != 0)
		return (ft_strdup(env_value));
	return (ft_strdup("2"));
}

static char	*valid_argument(t_shell *shell, char *str, int j)
{
	int	i;
	char 	*ret;

	i = ft_strlen(str);
	ret = ft_calloc(i, sizeof(char));
	i = 0;
	while (str[j])
	{
		if (!ft_isalnum(str[j]))
			break ;
		ret[i] = str[j];
		i++;
		j++;
	}
	return (ret);
}

static char	*check_expand(t_shell *s, char *str)
{
	int i;
	int	j;
	char *ret;
	char *retu;

	ret = NULL;
	retu = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[++i])
			{
				retu = valid_argument(s, str, i);
				retu = get_env_ret(s, retu);
				if (ft_strncmp(retu, "\2", 2) != 0)
				{
					ret = ft_strjoin(ret, retu);
					ret = ft_strjoin(ret, "\0");
					j += ft_strlen(ret);
					i += ft_strlen(retu) - 1;
				}
			}
			else
				return (ft_strdup("2"));
		}
		else
			ret[j++] = str[i];
		i++;
	}
	free(retu);
	free(str);
	return (ret);
}

void	expander(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
	while (cmd)
	{
		while (cmd->args[i] != NULL)	
		{
			cmd->args[i] = check_expand(shell, cmd->args[i]);
			i++;
		}
		clean_expand_cmd(cmd);
		cmd = cmd->next;
	}
}
// echo ${PWD/atacu}
// >|cat
// CAT << "$USER