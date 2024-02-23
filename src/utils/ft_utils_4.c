/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:26:29 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 21:20:57 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int fd1, int fd2)
{
	close_fd(fd1);
	close_fd(fd2);
}

void	cmd_error(t_shell *s, char *str)
{
	static struct stat	stats;

	if (lstat(str, &stats) != 0 && ft_strlen(str) != 0)
	{
		s->status = 127;
		ft_putstr_fd(str, 2);
		ft_putstr_ln(": command not found", 2);
	}
	if (S_ISDIR(stats.st_mode))
	{
		s->status = 126;
		ft_putstr_fd(str, 2);
		ft_putstr_ln(": Is a directory", 2);
	}
}

char	*ft_strchr_quotes(char *s, int c)
{
	int		flag;
	size_t	i;

	flag = 0;
	i = 1;
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
	return (0);
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
