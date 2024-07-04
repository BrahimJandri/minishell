/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/04 09:41:42 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
    t_token *head;
    t_token *tmp;
    
    head = NULL;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break ;
		while(rl[0] == '\0')
			rl = readline("minishell> ");
		first_parse(rl, &head);
        tmp = head;
        while (tmp)
        {
            printf("[TOKEN = %s] == [TYPE = %s]\n", tmp->token, tmp->type);
            tmp = tmp->next;   
        }
        free_tokens(head);
        head = NULL;
	}
	free(rl);
	return (0);
}

