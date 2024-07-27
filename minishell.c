/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/27 10:05:54 by bjandri          ###   ########.fr       */
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
	shell->env = create_env(envm);
}

void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nMiniShell>", 12);
}

void ft_remove_quotes(t_parser *parse)
{
	t_parser *tmp;

	tmp = parse;
	remove_quotes(tmp->str[0]);
}

void ft_start(t_mini shell)
{	
	while(1)
	{
		shell.rl = readline("MiniShell> ");
		if (!shell.rl)
			break;
		first_parse(shell.rl, &shell.head);
		parsing(&shell.head, &shell.cmds);
		execute(shell.cmds, &shell, &shell.env);
		free_tokens(shell.head);
		free_parser(shell.cmds);
		shell.head = NULL;
		shell.cmds = NULL;
	}
}

int main(int ac, char **av, char **envm)
{
	(void)ac;
	(void)av;
	t_mini	shell;
	
	init_mini(&shell,envm);
	signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
	ft_start(shell);
	free(shell.rl);
	return (0);
}
