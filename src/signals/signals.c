/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:36:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/19 16:27:34 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;
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
		ft_putstr_fd("\n", 2);
		close(STDIN_FILENO); 
		exit(0);
	}
	if (signal == SIGUSR1)
	{
	    g_signal = 11;
		ft_putstr_fd("HereDoc delimited by end-of-line\n", 2);
		close(STDIN_FILENO);
	}
	
}

void	set_signal_action(int sig_state)
{
	if (sig_state == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		//signal(SIGUSR1, SIG_IGN);
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
