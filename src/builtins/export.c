/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:25:03 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/18 22:29:57 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_env(char **env_copy)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	len = ft_double_strlen(env_copy);
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], ft_strlen(env_copy[j])) > 0)
			{
				tmp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env_copy);
}

// void	print_export(char **s, int out)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*tmp;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		tmp = ft_strdup(s[i]);
// 		while (tmp[j])
// 		{
// 			if (tmp[j] )
// 			j++;
// 		}
// 		free(tmp);
// 		i++;
// 	}
	
// }

void	export_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	char	*var_name;
	char	*var_value;

	(void) in;
	if (!cmd->args[1])
		print_export(s->export, out);
	else
	{
		var_name = ft_strdup(cmd->args[1]);
		var_value = ft_strchr(var_name, '=');
		if (var_value != NULL)
			s->export = overwrite_var(s->export, var_name, 0);///
		else
			if (var_exist(s->export, var_name) == 1)
				s->export = add_var_export(s->export, var_name, 0);
		free(var_name);
	}
}
