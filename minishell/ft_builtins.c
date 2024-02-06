/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:21:15 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 15:32:23 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echocmd(char *str){
	char *echostr;
	int i = 0;
	int aux = 5;

	while(str[i])
		i++;

	echostr = malloc(sizeof(char) * i +1);
	i = 0;
	if (str[5] == '-' && str[6] == 'n')
	{
		aux += 3;
	}			//tratar de -n varios
	while(str[i+aux]){
		echostr[i] = str[i+aux];
		i++;
	}
	if (aux == 5)
		echostr[i] = '\n';
	else
		echostr[i-1] = '\0';
	printf("%s", echostr);

	free(echostr);
}

void	built_ins(t_paths *p){
	int i;

	i = 0;
	if (strncmp(p->input, "env", ft_strlen(p->input)) == 0)
	{
		while(p->envp[i])
			printf("%s", p->envp[i]);
	}
	if (strncmp(p->input, "pwd", ft_strlen(p->input)) == 0)
		printf("%s", p->pwd);
	if (strncmp(p->input, "echo", 4) == 0)
		echocmd(p->input);
		
}
