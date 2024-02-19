/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:16:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/19 14:10:56 by gcatarin         ###   ########.fr       */
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

char	*flag_return(int flag, char *new)
{
	if (flag == 0)
		return (new);
	free(new);
	return (NULL);
}

int	ft_double_strlen(char **s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	close_fd(int fd)
{
	if (fd != 0 && fd != 1 && fd != -1)
		close(fd);
	return (1);
}

int	ft_biggerncmp(char *s1, char *s2, int size_s1)
{
	int	size_s2;
	int	ret;

	size_s2 = ft_strlen(s2);
	ret = 0;
	if (size_s1 > size_s2)
	{
		ret = ft_strncmp(s1, s2, size_s1);
		free(s2);
		return (ret);
	}
	ret = ft_strncmp(s1, s2, size_s2);
	free(s2);
	return (ret);
}
