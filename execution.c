/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:19:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/20 16:40:55 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(char *command, char **args, t_mini *shell)
{
    execve(command, args, shell->envp);
}

void execute_builtin(t_parser *args, t_env *env)
{
    printf("builtin: %s\n", args->str[0]);
    if(ft_strncmp(args->str[0], "echo", 4) == 0)
        echo_builtin(args->str);
    else if(ft_strncmp(args->str[0], "pwd", 3) == 0)
        pwd_builtin();
    else if(ft_strncmp(args->str[0], "cd", 2) == 0)
        cd_builtin(args->str);
    else if(ft_strncmp(args->str[0], "export", 6) == 0)
        export_builtin(args->str);
    else if(ft_strncmp(args->str[0], "unset", 5) == 0)
        unset_builtin(args->str);
    else if(ft_strncmp(args->str[0], "env", 3) == 0)
        env_builtin(env);
    else if(ft_strncmp(args->str[0], "exit", 4) == 0)
        exit_builtin(args->str);
    else
        ft_putendl_fd("minishell: command not found", 2);
}

void execute(t_parser *parser, t_mini *shell, t_env *env)
{
    t_parser *tmp;

    tmp = parser;
    while (tmp)
    {
        if (tmp->builtin)
            execute_builtin(tmp, env);
        else
            execute_command(tmp->str[0], tmp->str, shell);
        tmp = tmp->next;
    }
}


