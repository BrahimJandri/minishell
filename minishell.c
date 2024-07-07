/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/07 10:41:23 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
	t_lexer	*head;

	head = NULL;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break ;
		first_parse(rl, &head);
		while(head)
		{
			printf("word [%s]  type[%i] index[%d] \n", head->token, head->type, head->index);
			head = head->next;
		}
		free_tokens(head);
		head = NULL;
	}
	free(rl);
	return (0);
}
