/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/10 19:23:37 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_shell *shell, char **env)
{
	char	*line;
	char	*str;

	shell->env = copy_array(env);
	while (1)
	{
		line = readline("Minishell: ");
		if (line == NULL)
			free_shell(shell);
		str = ft_strtrim(line, " ");
		if (str && *str != '\0')
		{
			add_history(str);
			tokeniser(str, shell);
			// ft_list(shell->cmd);
			free(str);
			free(line);
			if (shell->cmd)
				executor(shell);
			shell->cmd = free_cmds(shell->cmd);
		}
		else
		{
			free(str);
			free(line);
		}
	}
}

int main(int ac, char **av, char **env)
{
	static t_shell shell;

	(void) ac;
	(void) av;
	//set_signal_action();
	minishell_loop(&shell, env);
}
