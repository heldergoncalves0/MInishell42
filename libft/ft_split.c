/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:57:47 by helferna          #+#    #+#             */
/*   Updated: 2024/02/10 18:01:01 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	count_word(const char *s, char c)
// {
// 	int	trigger;
// 	int	i;

// 	i = 0;
// 	trigger = 0;
// 	while (*s)
// 	{
// 		if (*s != c && trigger == 0)
// 		{
// 			trigger = 1;
// 			i++;
// 		}
// 		else if (*s == c)
// 			trigger = 0;
// 		s++;
// 	}
// 	return (i);
// }

// static char	*word(const char *s, int start, int finish)
// {
// 	size_t	i;
// 	char	*new_str;

// 	i = 0;
// 	new_str = malloc(sizeof(char) * (finish - start + 1));
// 	while (start < finish)
// 		new_str[i++] = s[start++];
// 	new_str[i] = '\0';
// 	return (new_str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	**split;
// 	int		index;

// 	i = 0;
// 	j = 0;
// 	index = -1;
// 	split = malloc (sizeof(char *) * (count_word(s, c) + 1));
// 	if (!split || !s)
// 		return (0);
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] != c && index < 0)
// 			index = i;
// 		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
// 		{
// 			split[j++] = word(s, index, i);
// 			index = -1;
// 		}
// 		i++;
// 	}
// 	split[j] = 0;
// 	return (split);
// }

static int	get_length(char c, char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s != c && *s)
				s++;
			len++;
		}
	}
	return (len);
}

static char	*new_word(const char *s, int start, int end, int len)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		new = (char *)malloc(sizeof(char) * len + 1);
	while (start < end)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		end;
	int		index_split;

	if (!s)
		return (ft_calloc(sizeof(char *), 1));
	split = (char **)malloc(sizeof(char *) * (get_length(c, (char *)s) + 1));
	if (!split || !s)
		return (0);
	i = 0;
	index_split = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != '\0')
		{
			end = i;
			while (s[end] && s[end] != c)
				end++;
			split[index_split++] = new_word(s, i, end, end - i);
			i = end;
		}
		else
			i++;
	}
	split[index_split] = 0;
	return (split);
}
