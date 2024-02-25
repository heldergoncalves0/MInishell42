/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/25 16:43:12 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_input(t_shell *shell, char *str, char *line)
{
	add_history(str);
	free(line);
	terminal()->is_exec = 1;
	if (tokeniser(str, shell) == 0)
	{
		free(str);
		if (sintax_verify(shell) == 0)
		{
			split_redirect(shell, 0);
			expander(shell);
			handle_quotes(shell);
			execute_redirects(shell, shell->cmd);
			executor(shell);
		}
	}
	else
		free(str);
	terminal()->is_exec = 0;
	shell->cmd = free_cmds(shell->cmd);
}

void	minishell_loop(t_shell *shell, char **env)
{
	char	*line;
	char	*str;

	shell->env = copy_array(env);
	shell->export = sort_env(copy_array(shell->env), 0);
	while (1)
	{
		shell->num_cmds = 0;
		set_signal_action(0);printf("STATUS: %d\n", shell->status);
		line = readline("Minishell: ");
		if (line == NULL)
			free_shell(shell, shell->status);
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
