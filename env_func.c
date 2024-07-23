/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:26:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/23 19:26:30 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env	*ft_new_env(char *key, char *value)
// {
// 	t_env	*new_node;

// 	new_node = (t_env *)malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->key = key;
// 	new_node->value = value;
// 	new_node->next = NULL;
// 	return (new_node);
// }

void	ft_lstadd(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
char *ft_strnlen(const char *str, char delimiter)
{
    int i = 0;
	int j = 0;
    while (str[i] && str[i] != delimiter)
        i++;
    
    char *result = malloc(i + 1);
    if (!result)
        return NULL;

    while (j < i)
    {
        result[j] = str[j];
		j++;
    }
    result[i] = '\0';
    return result;
}

t_env *create_env(char **env)
{
	t_env	*head;
	char	*key;
	char	*value;
	int		i;
	int res;

	i = 0;
	head = NULL;
	while (env[i])
	{
		key = ft_strnlen(env[i], '=');
		res = ft_strlen(key);		
		value = ft_strdup(env[i] + res + 1);
		ft_lstadd(&head, ft_new_env(key, value));
		i++;
	}
	return (head);
}

