/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/07 11:37:54 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_msg(char *s){
	write(2, s, ft_strlen(s));
}

void	exitcase(t_paths *p)
{
	printf("exit\n");
	leave(p);
}

void	leave(t_paths *p)
{
	//int i;

	rl_clear_history();
	free(p);
	// free(p->input);
	// i = 0;
	// while(p->args[i])
	// {
	// 	free(p->args[i]);
	// 	i++;
	// }
	// i = 0;
	// while(p->envp[i])
	// {
	// 	free(p->envp[i]);
	// 	i++;
	// }
	// free(p->path);
	// free(p->pwd);
	// i = 0;
	// while(p->paths[i])
	// {
	// 	free(p->paths[i]);
	// 	i++;
	// }
	 exit(0);
}