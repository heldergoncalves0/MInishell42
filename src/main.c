/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/07 21:47:38 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(t_shell *shell)
{
	char	*line;
	char	*str;

	while (1)
	{
		line = readline("Minishell: ");
		if (line == NULL)
			exitcase(shell, "exit");
		str = ft_strtrim(line, " ");
		if (str && *str != '\0')
		{
			add_history(str);
			tokeniser(str, shell);	
		}		
		free(str);
		free(line);
	}
}

int main(int ac, char **av, char **env)
{
	static t_shell shell;

	(void) ac;
	(void) av;
	(void) env;
	minishell_loop(&shell);
}
