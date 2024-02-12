/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/11 14:57:11 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set(char *envar, char *content, char **env)
{
	char	*tmp;
	char	*new;
	int		i;

    i = 0;
	new = ft_strjoin(envar, "=");
	tmp = ft_strjoin(new, content);
	while (ft_strncmp(env[i], envar, ft_strlen(envar)))
		i++;
    env[i] = ft_strdup(tmp);
    free(tmp);
	free(new);
}

void	cd_cmd(char *path, char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7))
		i++;
	if (env[i])
		printf("%s\n", env[i] + 4);
    set("PWD", path, env);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (env[i])
		printf("%s\n", env[i] + 4);
}
