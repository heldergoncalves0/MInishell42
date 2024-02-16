/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/02/16 17:05:15 by helferna         ###   ########.fr       */
=======
/*   Updated: 2024/02/16 17:10:01 by gcatarin         ###   ########.fr       */
>>>>>>> parser
=======
/*   Updated: 2024/02/16 17:17:00 by gcatarin         ###   ########.fr       */
>>>>>>> parser
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
		handle_quotes(shell);
		split_redirect(shell);
		execute_redirects(shell, shell->cmd);
<<<<<<< HEAD
		ft_list(shell->cmd);
		//expander(shell);
		//ft_list(shell->cmd);
=======
		expander(shell);
		//handle_quotes(shell);
		ft_list(shell->cmd);
>>>>>>> parser
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
