/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/06 16:39:20 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set(char *envar, char *content, char **env)
{
	char    *tmp;
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
void	cd(t_mini *mini, char *path, char **env)
{
	int i = 0;
	while (ft_strncmp(env[i], "PWD", ft_strlen("PWD")))
		i++;
	printf("OLDPWD: %s\n", env[i]);
    set("PWD", path, env);
	printf("PWD: %s\n", env[i]);
}
