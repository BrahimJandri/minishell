/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:19:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/20 12:57:32 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(char *command, char **args, t_mini *shell)
{
    execve(command, args, shell->envp);
}

void execute_builtin(t_parser *args)
{
    if((args->builtin == ECHO))
        echo_builtin(args->str);
    else if((args->builtin == PWD))
        pwd_builtin();
    else if((args->builtin == CD))
        cd_builtin(args->str);
    else if((args->builtin == EXPORT))
        export_builtin(args->str);
    else if((args->builtin == UNSET))
        unset_builtin(args->str);
    else if((args->builtin == ENV))
        env_builtin();
    else if((args->builtin == EXIT))
        exit_builtin(args->str);
    else
        ft_putendl_fd("minishell: command not found", 2);
}

void execute(t_parser *parser, t_mini *shell)
{
    t_parser *tmp;

    tmp = parser;
    while (tmp)
    {
        if (tmp->builtin)
            execute_builtin(tmp);
        else
            execute_command(tmp->str[0], tmp->str, shell);
        tmp = tmp->next;
    }
}


