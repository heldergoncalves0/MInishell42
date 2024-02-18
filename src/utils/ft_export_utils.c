/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:16:10 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/18 22:27:11 by gcatarin         ###   ########.fr       */
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
	char	*var_name;

	new = ft_calloc(sizeof(char **), ft_double_strlen(s) + 2);	
	i = 0;
	j = 0;
	while (s[i])
	{
		var_name = get_var_name(s[i]);
		if (ft_biggerncmp(str, var_name, ft_strlen(str), ft_strlen(var_name)) < 0 && flag == 0)
		{
			new[j] = ft_strdup(str);
			flag++;
		}
		else
			new[j] = ft_strdup(s[i++]);
		free(var_name);
		j++;
	}
	if (flag == 0)
		new[j] = ft_strdup(str);
	free_array(s);
	return (new);
}

char	**copy_array_export(char **s, char *str, char *c)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(sizeof(char *), ft_double_strlen(s) + 2);
	while (s[++i])
		new[i] = ft_strdup(s[i]);
	new[i] = ft_strjoin(str, c);
	free_array(s);
	return (new);
}

int	var_exist(char **s, char *str)
{
	size_t	i;
	char	*var_name;

	i = -1;
	while (s[++i])
	{
		var_name = get_var_name(s[i]);
		if (ft_biggerncmp(str, var_name, ft_strlen(str), ft_strlen(var_name)) == 0)
		{
			free(var_name);
			return (0);
		}
		free(var_name);
	}
	return (1);
}

char	**overwrite_var(char **s, char *str, int flag)
{
	char	**new;
	size_t	i;
	size_t	j;
	char	*var_name;

	new = ft_calloc(sizeof(char **), ft_double_strlen(s) + 2);	
	i = 0;
	j = 0;
	while (s[i])
	{
		var_name = get_var_name(s[i]);
		if (ft_biggerncmp(str, var_name, ft_strlen(str), ft_strlen(var_name)) <= 0 && flag == 0)
		{
			new[j] = ft_strdup(str);
			flag++;
		}
		else
			new[j] = ft_strdup(s[i++]);
		free(var_name);
		j++;
	}
	if (flag == 0)
		new[j] = ft_strdup(str);
	free_array(s);
	return (new);
}