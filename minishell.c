/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/06 21:23:40 by bjandri          ###   ########.fr       */
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
			printf("word [%s]  type[%i]  index[] \n", head->token, head->type);
			head = head->next;
		}
		head->i = 0;
		free_tokens(head);
		head = NULL;
	}
	free(rl);
	return (0);
}
