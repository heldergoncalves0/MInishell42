/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:26:29 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/25 18:03:15 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int fd1, int fd2)
{
	close_fd(fd1);
	close_fd(fd2);
}

int	cmd_error(char *str)
{
	static struct stat	stats;
	
	if (lstat(str, &stats) != 0)
	{
		if (ft_strlen(str) != 0)
			ft_putstr_fd(str, 2);
		else
			ft_putstr_fd("\'\'", 2);
		ft_putstr_ln(": command not found", 2);
		return (127);
	}
	if (errno == EACCES)
	{
		if (S_ISDIR(stats.st_mode))
			dir_error(str);
		return (126);
	}
	if (errno == ENOENT)
		return (2);
	return (0);
}

char	*ft_strchr_quotes(char *s, int c)
{
	int		flag;
	size_t	i;

	flag = 0;
	i = 1;
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == 34 && flag == 0)
			flag = 1;
		else if (*s == 39 && flag == 0)
			flag = 2;
		else if (*s == 34 && flag == 1)
			flag = 0;
		else if (*s == 39 && flag == 2)
			flag = 0;
		else if ((unsigned char)c == *s && flag < 2 && \
								ft_ismorealnum(s[i]) == 1)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	ft_strint_quotes(char *s, int c)
{
	int		flag;
	size_t	i;
	size_t	counter;

	flag = 0;
	i = 1;
	counter = 1;
	while (*s)
	{
		if (*s == 34 && flag == 0)
			flag = 1;
		else if (*s == 39 && flag == 0)
			flag = 2;
		else if (*s == 34 && flag == 1)
			flag = 0;
		else if (*s == 39 && flag == 2)
			flag = 0;
		else if ((unsigned char)c == *s && flag < 2 && \
								ft_ismorealnum(s[i]) == 1)
			return (counter);
		s++;
		counter++;
	}
	return (0);
}

char	*valid_argument(char *ret)
{
	int	i;

	i = 0;
	while (ret[i])
	{
		if (ret[i] == '?')
		{
			ret[++i] = '\0';
			break ;
		}
		else if (!ft_isalnum(ret[i]))
		{
			ret[i] = '\0';
			break ;
		}
		i++;
	}
	return (ret);
}
