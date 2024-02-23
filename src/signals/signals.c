/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:36:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 21:19:55 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_parent_handler(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (signal == SIGINT)
		ft_putstr_fd("\n", 2);
}

static void	sig_hd_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 10;
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
