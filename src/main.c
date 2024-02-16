/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/16 17:10:01 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_input(t_shell *shell, char *str, char *line)
{
	add_history(str);
	free(line);
	if (tokeniser(str, shell))
	{
		free(str);
		split_redirect(shell);
		execute_redirects(shell, shell->cmd);
		expander(shell);
		handle_quotes(shell);
		ft_list(shell->cmd);
		executor(shell);
	}
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

int	main(int ac, char **av, char **env)
{
	static t_shell	shell;

	(void) ac;
	(void) av;
	set_signal_action();
	minishell_loop(&shell, env);
}
