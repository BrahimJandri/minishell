/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:19:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/18 12:33:32 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	execute_command(char *command, char **args)
{
	execv(command, args);
}

void	execute_builtin(char **args)
{
	if (!ft_strncmp(args[0], "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(args[0], "echo", 4))
		echo_builtin(args);
	else if (!ft_strncmp(args[0], "cd", 2))
		cd_builtin(args);
	else if (!ft_strncmp(args[0], "export", 6))
		export_builtin(args);
	else if (!ft_strncmp(args[0], "unset", 5))
		unset_builtin(args);
	else if (!ft_strncmp(args[0], "env", 3))
		env_builtin();
	else if (!ft_strncmp(args[0], "exit", 4))
		exit_builtin(args);
	else
		ft_putendl_fd("minishell: command not found", 2);
}

void	execute(t_parser *parser)
{
	t_parser	*tmp;

	tmp = parser;
	while (tmp)
	{
		if (tmp->builtin)
			execute_builtin(tmp->str);
		else
			execute_command(tmp->str[0], tmp->str);
		tmp = tmp->next;
	}
}
