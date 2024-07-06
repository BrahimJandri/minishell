/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/06 10:08:54 by bjandri          ###   ########.fr       */
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
		free_tokens(head);
		head = NULL;
	}
	free(rl);
	return (0);
}
