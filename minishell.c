/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/20 14:59:13 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_mini *shell, char **envm)
{
	int i;

	i = 0;
	while(envm[i])
	{
		if(ft_strncmp("PATH=", envm[i], 5) == 0)
		{
			shell->path = ft_split(envm[i] + 5, ':');
			break;
		}
		i++;
	}
	shell->envp = arr_dup(envm);
	shell->cmds = NULL;
	shell->head = NULL;
	shell->rl = NULL;	
	shell->pipes = 0;
}

int main(int ac, char **av, char **envm)
{
	(void)ac;
	(void)av;
	t_mini	shell;
	
	init_mini(&shell,envm);
	while (1)
	{
		shell.rl = readline("minishell> ");
		if (!shell.rl)
			break;
		// rm_quote(shell.rl);
		first_parse(shell.rl, &shell.head);
		parsing(&shell.head, &shell.cmds);
		execute(shell.cmds, &shell);
		free_tokens(shell.head);
		free_parser(shell.cmds);
		shell.head = NULL;
		shell.cmds = NULL;
	}
	free(shell.rl);
	return (0);
}
