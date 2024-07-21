/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/21 15:14:26 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    if (!args[i])
    {
        write(1, "\n", 1);
        return ;
    }
    while (args[i] && is_n_flag(args[i]))
    {
        n_flag = 1;
        i++;
    }    
    while (args[i])
    {
        remove_quotes(args[i]);
        write(1, args[i], ft_strlen(args[i]));
        if (args[i++ + 1])
            write(1, " ", 1);
    }
    if (!n_flag)
        write(1, "\n", 1);
}

char *getenv_value(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

void setenv_value(t_env **env, const char *key, const char *value)
{
    t_env *temp = *env;
    while (temp)
    {
        if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
        {
            free(temp->value);
            temp->value = ft_strdup(value);
            return;
        }
        temp = temp->next;
    }

    t_env *new_node = malloc(sizeof(t_env));
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = *env;
    *env = new_node;
}

void update_env(t_env **env, const char *oldpwd, const char *newpwd)
{
    if (oldpwd)
        setenv_value(env, "OLDPWD", oldpwd);
    if (newpwd)
        setenv_value(env, "PWD", newpwd);
}

void cd_builtin(char **args, t_env **env)
{
    char *path;
    
    if(args[1] != NULL && args[2] != NULL)
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        return ;
    }
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
        update_env(env,"OLDPWD", getenv("PWD"));
        update_env(env,"PWD", path);
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

void export_builtin(char **args, t_mini *shell)
{
    int i;
    char *key;
    char *value;
    int j;

    j = 0;
    if(!args[1])
    {
        while(shell->export[j])
            ft_putendl_fd(shell->export[j++], 1);
    }
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


void env_builtin(t_env **env)
{
    print_env(env);
}
