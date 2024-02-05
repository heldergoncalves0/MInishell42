/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:46:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/05 17:59:51 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

void tokeniser(){
	ft_
}

int main(){
	char *string;
	char **strings;
	int i;

	i = 0;
	string = readline("aqui: ");
	printf("\n%s -\n", string);
	strings = ft_split(string , ' ');
	while(strings[i])
		printf("%s\n", strings[i++]);
	
	
	
	free(string);
}