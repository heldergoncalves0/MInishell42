/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:31 by helferna          #+#    #+#             */
/*   Updated: 2024/02/20 18:36:38 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*valid_argument(char *ret)
{
	int	i;

	i = 0;
	while (ret[i])
	{
		if (ret[i] != '?' && !ft_isalnum(ret[i]))
		{
			ret[i] = '\0';
			break ;
		}
		i++;
	}
	return (ret);
}

char	*get_env_return(t_shell *s, char *ret)
{
	char	*env_value;

    if (ft_strncmp(ret, "?", 2) == 0)
		return (ft_itoa(s->status));
	else
	{
		env_value = get_env(s, ret);
		if (ft_strlen(env_value) != 0)
			return (ft_strdup(env_value));
		return (ft_strdup(""));
	}
}

static int	ft_isquoted(char c, int flag)
{
	if (c == 39 && flag == 0)
		return(1);
	return (0);
}

char	*clear_expand(char *str, char *arg, char *tmp, int quote)
{
	size_t	i;
	size_t	j;
	char	*ret;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	ret = ft_calloc(sizeof(char), (ft_strlen(str) + ft_strlen(tmp)) + 1);
	while (str[j])
	{
		quote = ft_isquoted(str[i], quote);
		if (str[j] == '$' && flag == 0)
		{
			while((str[++j] == *arg) && *arg)
				flag = *arg++;
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

char	*expand_argument(t_shell *s, char *str, size_t j, int flag)
{
	char	*arg;
	char	*tmp;

	arg = NULL;
	tmp = NULL;
	while (str[j])
	{
		if (str[j] == 39 && flag == 0)
			flag = 1;
		else if (str[j] == '$' && flag == 0)
		{
			arg = valid_argument(ft_strdup(ft_strchr_quotes(str, '$') + 1));
			j += ft_strlen(arg) + 1;
			tmp = get_env_return(s, arg);
			str = clear_expand(str, arg, tmp, 0);
			free(tmp);
			free(arg);
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
	size_t	i;
	size_t	j;
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
	while (cmd)
	{
		if (cmd->args[i] != NULL)
		{
			j = -1;
			while (cmd->args[++j])
			{
				while (ft_strchr_quotes(cmd->args[j], '$') != NULL)
					cmd->args[j] = expand_argument(shell, cmd->args[j], 0, 0);
			}
			j++;
		}
		cmd = cmd->next;
	}
}
// echo ${PWD/atacu}

// CAT << "$USER"

//cat .... ctrl + c
