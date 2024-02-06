/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:46:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 13:42:21 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

void tokeniser(){
	//ft_
}

t_paths *paths_init(char **env){
	t_paths *p;
	int i;
	
	p =(t_paths *)malloc(sizeof(t_paths));
	if (!p)
		return (0);
	p->input = NULL;
	p->args = NULL;
	p->envp = env;
	i = 0;
	while(env[i]){
		if(strncmp(env[i], "PWD=", 4) == 0)
			p->pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
		i++;
	}
	i = 0;
	while(env[i]){
		if(strncmp(env[i], "PATH=", 5) == 0)
			p->path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
		i++;
	}

	return (p);
}

int main(int ac, char **av, char **env){
	t_paths *p;
	
	char *string;
	char **strings;
	int i;

	i = 0;
	if (ac != 1 && av[0])
	{
		printf("%s: ", av[0]);
		while (av[i])
			printf("%s", av[i++]);
		printf(": No such file or directory\n"); //se a file existir
		exit(0);
	}

	p = paths_init(env);
	string = readline("Minishell>");		//prompt
	strings = ft_split(string , ' ');
	
	add_history(string);

	p->input = string;
	printf("\n%s -\n", p->input);
	
	p->args = strings;
	while(p->args[i])
		printf("%s\n", p->args[i++]);
	i = 0;
	
	printf("%s\n", p->pwd);
	printf("%s\n", p->path);

	free(string);
}