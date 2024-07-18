/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/18 12:45:01 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int pwd_builtin(void)
{
    char *buf;

    buf = getcwd(NULL, 0);
    ft_putendl_fd(buf, 1);
    free(buf);
    return(0);
}

void echo_builtin(char **args)
{
    int i;
    int n_flag;
    
    i = 1;
    n_flag = 0;

    remove_quotes(args[i]);
    while (args[i] && is_n_flag(args[i]))
    {
        n_flag = 1;
        i++;
    }    
    while (args[i])
    {
        remove_quotes(args[i]);
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!n_flag)
        write(1, "\n", 1);
}

void cd_builtin(char **args)
{
    char *path;

    if (!args[1])
        path = getenv("HOME");
    else if (!ft_strncmp(args[1], "-", 1))
        path = getenv("OLDPWD");
    else
        path = args[1];
    if (chdir(path) == -1)
        ft_putendl_fd("minishell: cd: no such file or directory", 2);
    else
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", path, 1);
    }
}

void exit_builtin(char **args)
{
    int i;

    i = 1;
    if (args[i])
        exit(ft_atoi(args[i]));
    else
        exit(0);
}

void unset_builtin(char **args)
{
    int i;

    i = 1;
    while (args[i])
    {
        unsetenv(args[i]);
        i++;
    }
}

void export_builtin(char **args)
{
    int i;
    char *key;
    char *value;

    i = 1;
    while (args[i])
    {
        key = ft_strtok(args[i], "=");
        value = ft_strtok(NULL, "=");
        if (value)
            setenv(key, value, 1);
        else
            setenv(key, "", 1);
        i++;
    }
}


void env_builtin(void)
{
    int i;

    extern char **environ;
    i = 0;
    while (environ[i])
    {
        ft_putendl_fd(environ[i], 1);
        i++;
    }
}
