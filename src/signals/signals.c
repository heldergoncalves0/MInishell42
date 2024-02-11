/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:36:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/10 18:40:26 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		printf("\nIntercepted SIGINT!\n");
		//leave(s);
}

void set_signal_action(void)
{
	struct sigaction	act;	
	
	ft_bzero(&act, sizeof(act));	// Set all of the structure's bits to 0 to avoid errors - relating to uninitialized variables...
	
	act.sa_handler = &sigint_handler;// Set the signal handler as the default action

	sigaction(SIGINT, &act, NULL);
}
