/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/13 17:35:05 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_input(t_shell *shell, char *str, char *line)
{
	add_history(str);
	if (tokeniser(str, shell))
	{
		//ft_list(shell->cmd);
		split_redirect(shell);
		execute_redirects(shell->cmd);
		ft_list(shell->cmd);
		executor(shell);
	}
	free(str);
	free(line);
	shell->cmd = free_cmds(shell->cmd);
}

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
			valid_input(shell, str, line);
		else
		{
			free(str);
			free(line);
		}
	}
}

int main(int ac, char **av, char **env)
{
	static t_shell	shell;

	(void) ac;
	(void) av;
	set_signal_action();
	minishell_loop(&shell, env);
}
