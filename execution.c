/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:19:48 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/25 15:52:22 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void pipe_execution(t_parser *parser, t_mini *shell)
{
    int fd[2];
    int status;
    pid_t pid;
    t_parser *tmp;

    tmp = parser;
    while (tmp)
    {
        if (tmp->next)
        {
            pipe(fd);
            pid = fork();
            if (pid < 0)
            {
                ft_putendl_fd("minishell: fork failed", 2);
                return ;
            }
            if (pid == 0)
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
                execve(tmp->str[0], tmp->str, shell->envp);
            }
            else
            {
                waitpid(pid, &status, 0);
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
            }
        }
        tmp = tmp->next;
    }
    execve(tmp->str[0], tmp->str, shell->envp);
}

int pipe_check(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        if (ft_strncmp(args[i], "|", 1) == 0)
            return (1);
        i++;
    }
    return (0);
}

void execute_command(char *command, char **args, t_mini *shell)
{
    pid_t pid;
    int status;
    
    if(pipe_check(args))
    {
        pipe_execution(shell->cmds, shell);
        return ;
    }
    pid = fork();
    if (pid < 0)
    {
        ft_putendl_fd("minishell: fork failed", 2);
        return ;
    }
    if (pid == 0)
        execve(command, args, shell->envp);
    else
        waitpid(pid, &status, 0);
}


void execute_builtin(t_parser *args, t_env **env)
{
    if(args->str[0] == NULL || args->str[0][0] == '\0')
        return ;
    if(ft_strncmp(args->str[0], "echo", 4) == 0)
        echo_builtin(args->str);
    else if(ft_strncmp(args->str[0], "pwd", 3) == 0)
        pwd_builtin();
    else if(ft_strncmp(args->str[0], "cd", 2) == 0)
        cd_builtin(args->str, env);
    else if(ft_strncmp(args->str[0], "export", 6) == 0)
        export_builtin(args->str, env);
    else if(ft_strncmp(args->str[0], "unset", 5) == 0)
        unset_builtin(args->str, env);
    else if(ft_strncmp(args->str[0], "env", 3) == 0)
        env_builtin(env);
    else if(ft_strncmp(args->str[0], "exit", 4) == 0)
        exit_builtin(args->str);
    else
        ft_putendl_fd("minishell: command not found", 2);
}

void execute(t_parser *parser, t_mini *shell, t_env **env)
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


