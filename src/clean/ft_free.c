/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/07 15:34:16 by helferna         ###   ########.fr       */
=======
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/07 21:45:17 by gcatarin         ###   ########.fr       */
>>>>>>> parser
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exitcase(t_shell *p, char *s)
{
	write(2, s, ft_strlen(s));
	leave(p);
}

void	leave(t_shell *p)
{
	//int i;

<<<<<<< HEAD
	clear_history();
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
=======
	rl_clear_history();
	(void )p;
	//free as structs
	exit(0);
>>>>>>> parser
}