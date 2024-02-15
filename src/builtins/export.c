/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:25:03 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/15 14:58:38 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sort_env(char **env_copy)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	len = ft_double_strlen(env_copy);
	i = 0;
	j = i + 1;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], \
			ft_strlen(env_copy[j])) > 0)
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

void	print_sorted_env(t_shell *shell, int out)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = sort_env(copy_array(shell->env));
	while (env_copy[i])
	{
		ft_putstr_fd(env_copy[i++], out);
		ft_putstr_fd("\n", out);
	}
	free_array(env_copy);
}

void	export_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	char	*var_name;
	char	*var_value;

	if (!cmd->args[1])
		print_sorted_env(s, out);
	else
	{
		var_name = ft_strdup(cmd->args[1]);
		var_value = ft_strchr(var_name, '=');
		s->env = copy_array_export(s->env, var_name, "\0");
		if (var_value != NULL)
		{
			var_value = ft_substr(var_value, 1, ft_strlen(var_value) - 1);
			set_env(s, var_name, var_value);
		}
		free(var_name);
	}
}
