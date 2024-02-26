/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:36:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/26 13:48:39 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signal)
{
	if (signal == SIGINT && terminal()->is_exec == 0)
	{
		terminal()->status = 33280;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_parent_handler(int signal)
{
	if (signal == SIGQUIT && terminal()->is_exec == 0)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (signal == SIGINT && terminal()->is_exec == 0)
	{
		terminal()->status = 130;
		ft_putstr_fd("\n", 2);
	}
}

static void	sig_hd_handler(int signal)
{
	if (signal == SIGINT)
	{
		terminal()->hd = 10;
		close(STDIN_FILENO);
	}
}

void	set_signal_action(int sig_state)
{
	if (sig_state == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig_state == 1)
	{
		signal(SIGINT, sig_hd_handler);
		signal(SIGUSR1, sig_hd_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig_state == 2)
	{
		signal(SIGINT, sig_parent_handler);
		signal(SIGQUIT, sig_parent_handler);
	}
	if (sig_state == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
