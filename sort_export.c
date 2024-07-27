/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:21:42 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/27 10:28:51 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_env(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return i;
}

void swap_env(t_env **a, t_env **b)
{
    t_env *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_env(t_env **env_array, int count)
{
    int i;
    int swapped;

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (i < count - 1)
        {
            if (ft_strcmp(env_array[i]->key, env_array[i + 1]->key) > 0)
            {
                swap_env(&env_array[i], &env_array[i + 1]);
                swapped = 1;
            }
            i++;
        }
    }
}

void print_sorted_env(t_env **env)
{
    int count = count_env(*env);
    t_env **env_array = malloc(count * sizeof(t_env *));
    
    if (!env_array)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    t_env *current = *env;
    int i = 0;
    while (current)
    {
        env_array[i] = current;
        current = current->next;
        i++;
    }
    sort_env(env_array, count);
    i = 0;
    while (i < count)
    {
        if (env_array[i]->value)
            printf("declare -x %s=\"%s\"\n", env_array[i]->key, env_array[i]->value);
        else
            printf("declare -x %s\n", env_array[i]->key);
        i++;
    }
    free(env_array);
}
