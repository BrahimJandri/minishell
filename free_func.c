/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:05:33 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/30 10:06:16 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_lexer *head)
{
	t_lexer	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->word);
		free(tmp);
	}
}

void	free_parser(t_parser *head)
{
	t_parser	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}
