/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:31 by helferna          #+#    #+#             */
/*   Updated: 2024/02/26 13:59:15 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_return(t_shell *s, char *ret)
{
	char	*env_value;

	if (ft_strlen(ret) == 0)
		return (ft_strdup("$"));
	else if (ft_strncmp(ret, "?", 2) == 0)
		return (ft_itoa(s->status));
	else
	{
		env_value = get_env(s, ret);
		if (ft_strlen(env_value) != 0)
			return (ft_strdup(env_value));
		return (ft_strdup(""));
	}
	return (env_value);
}

static char	*clear_expand(char *str, char *arg, char *tmp, size_t index)
{
	size_t	i;
	size_t	j;
	int		quote;
	char	*ret;

	ret = ft_calloc(sizeof(char), (ft_strlen(str) + ft_strlen(tmp)) + 1);
	i = 0;
	j = 0;
	quote = 0;
	while (str[j])
	{
		quote = ft_isquoted(str[j], quote);
		if (j == index - 1 && quote < 2)
		{
			while ((str[++j] == *arg) && *arg)
				index = *arg++;
			while (*tmp)
				ret[i++] = *tmp++;
		}
		else
			ret[i++] = str[j++];
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}

static char	*expand(t_shell *s, char *arg, char *str, size_t index)
{
	char	*tmp;

	tmp = get_return(s, arg);
	str = clear_expand(str, arg, tmp, index);
	free(tmp);
	free(arg);
	return (str);
}

char	*expand_argument(t_shell *s, char *str, size_t j)
{
	int		flag;
	char	*arg;

	flag = 0;
	arg = NULL;
	while (str[j])
	{
		if (str[j] == 39 && flag == 0)
			flag = 1;
		else if (str[j] == '$' && flag == 0)
		{
			arg = valid_argument(ft_strdup(ft_strchr_quotes(str, '$') + 1));
			j += ft_strlen(arg) + 1;
			str = expand(s, arg, str, ft_strint_quotes(str, '$'));
			return (str);
		}
		if (str[j] == 39)
			flag = 0;
		j++;
	}
	return (str);
}

void	expander(t_shell *shell)
{
	size_t	j;
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		j = -1;
		while (cmd->args[++j])
		{
			while (ft_strchr_quotes(cmd->args[j], '$') != NULL)
			{
				cmd->args[j] = expand_argument(shell, cmd->args[j], 0);
				if (!cmd->args[j] || *cmd->args[j] == '\0')
					cmd->args = remove_expansions(cmd->args, j, 0);
			}
		}
		cmd = cmd->next;
	}
}
