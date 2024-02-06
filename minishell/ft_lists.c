/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:57:52 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 19:09:40 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_lstnew(int type, char *s)
{
	t_lex	*ptr;

	if (!(ptr = (t_lex*)malloc(sizeof(*ptr))))
		return (NULL);
	ptr->word = s;
	ptr->token = type;
	ptr->next = NULL;
	return (ptr);
}
/*
int	ft_lstsize(t_lex *l_lst)
{
	if (l_lst == NULL)
		return (0);
	else
		return (1 + ft_lstsize(l_lst->next));
}

void	ft_lstadd_back(t_lex **l_lst, t_lex *new)
{
	t_lex	*back;

	back = *l_lst;
	if (!back)
	{
		*l_lst = new;
		return ;
	}
	back = ft_lstlast(*l_lst);
	back->next = new;
}
*/
int	add_token(char *token, int type, t_lex *l_lst) //**
{
	t_lex	*node;
	(void)l_lst;
	node = ft_lstnew(type, token);
	if (!node)
		return (0);
	//ft_lstadd_back(l_lst, node);
	return (1);
}