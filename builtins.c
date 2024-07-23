/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/23 19:17:33 by bjandri          ###   ########.fr       */
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
	    // rm_quote(args[i]);
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

t_env *ft_new_env(const char *key, const char *value)
{
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
        return NULL;

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    return new_node;
}

void update_env(t_env **env, const char *key, const char *value)
{
    t_env *temp = *env;
    while (temp)
    {
        if (strcmp(temp->key, key) == 0)
        {
            free(temp->value);
            temp->value = strdup(value);
            return;
        }
        temp = temp->next;
    }
    t_env *new_node = ft_new_env(key, value);
    ft_lstadd(env, new_node);
}

void cd_builtin(char **args, t_env **env)
{
    char *path;
    char *oldpwd;

    if (args[1] != NULL && args[2] != NULL)
    {
        ft_putendl_fd("minishell: cd: too many arguments", 2);
        return;
    }
    oldpwd = getenv_value(*env, "PWD");
    if (!args[1])
        path = getenv_value(*env, "HOME");
    else if (!ft_strncmp(args[1], "-", 1))
        path = getenv_value(*env, "OLDPWD");
    else
        path = args[1];
    if (chdir(path) == -1)
        ft_putendl_fd("cd: no such file or directory", 2);
    else
        update_env(env, oldpwd, path);
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

void unsetenv_custom(t_env **env, const char *key)
{
    t_env *temp = *env;
    t_env *prev = NULL;

    while (temp)
    {
        if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
        {
            if (prev)
                prev->next = temp->next;
            else
                *env = temp->next;
            
            free(temp->key);
            free(temp->value);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void unset_builtin(char **args, t_env **env)
{
    int i = 1;

    while (args[i])
    {
        unsetenv_custom(env, args[i]);
        i++;
    }
}

int is_valid_identifier(const char *str)
{
    if (!str || !ft_isalpha(*str))
        return 0;
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return 0;
        str++;
    }
    return 1;
}

void export_builtin(char **args, t_env **env)
{
    int i;
    char *key;
    char *value;

    if (!args[1])
    {
        t_env *current = *env;
        while (current)
        {
            printf("declare -x %s=\"%s\"\n", current->key, current->value);
            current = current->next;
        }
        return;
    }

    i = 1;
    while (args[i])
    {
        char *arg = args[i];
        key = ft_strnlen(arg, '=');

        if (!is_valid_identifier(key))
        {
            ft_putendl_fd("minishell: export: not a valid identifier", 2);
            free(key);
            i++;
            continue;
        }

        if (strchr(arg, '='))
            value = strdup(strchr(arg, '=') + 1);
        else
            value = strdup("");

        if (value && strchr(arg, '=') == arg) // Check for cases like "export =value"
        {
            ft_putendl_fd("minishell: export: not a valid identifier", 2);
            free(key);
            free(value);
            i++;
            continue;
        }

        update_env(env, key, value);
        free(key);
        free(value);
        i++;
    }
}


void env_builtin(t_env **env)
{
    t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

