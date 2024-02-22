/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:16:10 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/22 13:01:35 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = ft_calloc(ft_strlen(str), 2);
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

char	**add_var_export(char **s, char *str, int flag)
{
	char	**new;
	size_t	i;
	size_t	j;

	new = ft_calloc(sizeof(char **), ft_double_strlen(s) + 2);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_biggerncmp(str, get_var_name(s[i]), \
		ft_strlen(str)) <= 0 && flag == 0)
		{
			new[j] = ft_strdup(str);
			flag++;
		}
		else
			new[j] = ft_strdup(s[i++]);
		j++;
	}
	if (flag == 0)
		new[j] = ft_strdup(str);
	free_array(s);
	return (new);
}

int	var_exist(char **s, char *str)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (ft_biggerncmp(str, get_var_name(s[i]), ft_strlen(str)) == 0)
			return (0);
	}
	return (1);
}

char	**overwrite_var(char **s, char *str, int flag, char *str_name)
{
	char	**new;
	size_t	i;

	new = ft_calloc(sizeof(char **), ft_double_strlen(s) + 2);
	i = 0;
	while (s[i])
	{
		if (ft_biggerncmp(str, get_var_name(s[i]), \
		ft_strlen(str)) == 0 && flag == 0)
		{
			new[i] = ft_strdup(str_name);
			flag++;
		}
		else
			new[i] = ft_strdup(s[i]);
		i++;
	}
	if (flag == 0)
		new[i] = ft_strdup(str_name);
	free_array(s);
	return (new);
}

int	valid_name(char *s, int in)
{
	size_t	i;

	i = 0;
	(void) in;
	if (s[0] == '=')
		return (1);
	if (s[i] == '_' && ft_strlen(s) < 2)
		return (1);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && s[i] != '_')
			return (1);
		i++;
	}
	if (s[0] == '_' && i < 2)
		return (1);
	return (0);
}
