/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:18:45 by helferna          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:47 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int main(int ac, char **av, char **env)
// {
// 	static t_mini mini;
// 	(void)ac;
// 	(void)av;
//     if (!executor(env, &mini))
// 	    return (1);
//     return (0);
// }

char	*get_prompt(char *pwd)
{
	int	i;
	int	j;
	char *prompt;

	j = 0;
	i = ft_strlen(pwd);
	prompt = (char *)malloc(sizeof(char) * i);
	while(i >= 0)
	{
		if (pwd[i] == '/')
			break;
		i--;
	}
	i--;
	while(i >= 0)
	{
		if (pwd[i] == '/')
			break;
		i--;
	}
	if (i > 0)
		prompt[j++] = '~';
	while(pwd[i])
		prompt[j++] = pwd[i++];
	prompt[j] = '>';
	return (prompt);
}

void	paths_init(char **env, t_paths *p)
{
	int i;

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
		if(strncmp(env[i], "OLDPWD=", 6) == 0)
			p->old_pwd = ft_substr(env[i], 6, ft_strlen(env[i]) - 6);
		i++;
	}	
	i = 0;
	while(env[i]){
		if(strncmp(env[i], "PATH=", 5) == 0)
			p->path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
		i++;
	}	
	p->paths = ft_split(p->path , ':');
	//p->prompt = get_prompt(p->pwd);
	p->prompt = "Minishell> ";
}

void debug(t_paths *p){
	int i;
	
	printf("\n%s -\n", p->input);
	i = 0;
	printf("%s\n", p->args);
	i = 0;
	printf("%s\n", p->pwd);
	printf("%s\n", p->old_pwd);
	printf("%s\n", p->path);
	while(p->paths[i])
		printf("%s //", p->paths[i++]);
}

void minishell_loop(t_paths *p){
	char *string;
	char *strings;
	
	while (1){
		string = readline(p->prompt);		//prompt
		handle_quotes(string);
		strings = ft_strtrim(string, " ");
		p->input = string;
		p->args = strings;

		add_history(string);
		if (strncmp(string, "exit", ft_strlen(string)) == 0)
		{
			free(string);
			exitcase(p);
		}
		tokeniser(p, p->lex_lst);
		printLinkedList(p->lex_lst);
		//debug(p);
		free(p->input);
	}
}

int main(int ac, char **av, char **env){
	static t_paths p;
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
	paths_init(env, &p);
	minishell_loop(&p);
	leave(&p);
}
