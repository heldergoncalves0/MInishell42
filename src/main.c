/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/21 11:11:01 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	valid_input(t_shell *shell, char *str, char *line)
{
	add_history(str);
	free(line);
	tokeniser(str, shell);
	free(str);
	if (sintax_verify(shell) == 0)
	{
		split_redirect(shell, 0);
		expander(shell);
		//ft_list(shell->cmd);
		handle_quotes(shell);
		if (execute_redirects(shell, shell->cmd) == 0)
			executor(shell);
	}
	shell->cmd = free_cmds(shell->cmd);printf("EXIT STAT: %d\n", shell->status);
}

void	minishell_loop(t_shell *shell, char **env)
{
	char	*line;
	char	*str;

	shell->env = copy_array(env);
	shell->export = sort_env(copy_array(shell->env), 0);
	while (1)
	{
		set_signal_action(0);
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
	minishell_loop(&shell, env);
}

// tcgetattr()