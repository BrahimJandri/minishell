/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/18 12:33:20 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(void)
{
	t_parser	*cmds;
	char		*rl;
	t_lexer		*head;

	head = NULL;
	cmds = NULL;
	while (1)
	{
		rl = readline("minishell$> ");
		if (!rl)
			break ;
		first_parse(rl, &head);
		parsing(&head, &cmds);
		execute(cmds);
		free_tokens(head);
		free_parser(cmds);
		head = NULL;
		cmds = NULL;
	}
	free(rl);
	return (0);
}

///////////----- LAST UPDATE --------/////////
// YOU FOUND THAT WHEN FREEING PIPE; IT FREES BUT IT DOES NOT MOVE TO THE NEXT NODE
// THIS IS YOU NEXT MISSION.