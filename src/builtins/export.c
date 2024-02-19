/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:25:03 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/19 14:42:22 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_env(char **env_copy, int i)
{
	int		j;
	char	*tmp;
	int		len;

	len = ft_double_strlen(env_copy);
	while (i < len)
	{
		j = i;
		while (++j < len)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], ft_strlen(env_copy[j])) > 0)
			{
				if (valid_name(env_copy[j], 0) == 0)
				{
					tmp = env_copy[i];
					env_copy[i] = env_copy[j];
					env_copy[j] = tmp;
				}
			}
		}
		i++;
	}
	return (env_copy);
}

void	print_export(char **s, int out)
{
	size_t	i;
	size_t	j;
	int		flag;

	j = -1;
	while (s[++j])
	{
		i = 0;
		flag = 0;
		while (s[j][i] && s[j][i] != '\n')
		{
			ft_putchar_fd(s[j][i], out);
			if (s[j][i] == '=' && flag == 0)
			{
				ft_putchar_fd('\"', out);
				flag++;
			}
			i++;
		}
		if (flag == 1)
			ft_putstr_ln("\"", out);
		else
			ft_putchar_fd('\n', out);
	}
}

void	export_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	char	*var_name;
	char	*var;

	if (!cmd->args[1])
		print_export(s->export, out);
	else if (valid_name(cmd->args[1], in))
	{
		var = ft_strdup(cmd->args[1]);
		var_name = get_var_name(var);
		if (ft_strchr(var, '=') != NULL)
		{
			if (var_exist(s->export, var_name) == 1)
				s->export = add_var_export(s->export, var, 0);
			else
				s->export = overwrite_var(s->export, var_name, 0, var);
		}
		else
			if (var_exist(s->export, var) == 1)
				s->export = add_var_export(s->export, var, 0);
		free(var);
		free(var_name);
	}
	else
		invalid_name_error(cmd->args[1]);
}
