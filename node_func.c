/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:26:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/30 10:07:29 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_lexer	*ft_new_token(char *content)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->word = content;
	new_node->token = type(content);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	static int	i;
	t_lexer		*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		i = 0;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->index = ++i;
}
