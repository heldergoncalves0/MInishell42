/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:16:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 11:11:25 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **s)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	while (s[len])
		len++;
	i = -1;
	new = ft_calloc(sizeof(char *), len + 1);
	while (s[++i])
		new[i] = ft_strdup(s[i]);
	return (new);
}

void	ft_list(t_cmd *c)
{
	int	i;

	i = 0;
	if (c == NULL)
		return ;
	printf("====== cmd %d ======\n", c->index);
	while (c->args[i])
		printf("arg:%s\n", c->args[i++]);
	if (c->next)
		ft_list(c->next);
	printf("\n");
}

char	*flag_return(int flag, char *new)
{
	if (flag == 0)
		return (new);
	free(new);
	return (NULL);
}

char	**search_heredocs(t_shell *s)
{
	int		i;
	int		hd_count;
	char	**hd_array;

	i= 0;
	hd_count = 0;
	while (s->cmd->args[i])
	{
		if (ft_strncmp(s->cmd->args[i], "<<", 3) == 0)
			hd_count++;
		i++;
	}
	hd_array = (char **)calloc(1, sizeof(char *));
	hd_count = 0;
	i = 0;
	while (s->cmd->args[i])
	{
		if (ft_strncmp(s->cmd->args[i], "<<", 3) == 0)
		{
			hd_array[hd_count++] = ft_strdup(s->cmd->args[++i]);
			s->cmd->args[i] = NULL;
			s->cmd->args[i - 1] = NULL;
		}
		i++;
	}
	return (hd_array);
}