/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/20 16:33:52 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

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

t_env *create_env(char **env)
{
	int i;
	char **tmp;
	t_env *head;
	t_env *new;
	
	i = 0;
	head = NULL;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		new = ft_new_env(tmp[0], tmp[1]);
		ft_lstadd(&head, new);
		// free_array(tmp);
		i++;
	}
	return head;
}

void print_env(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

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

int main(int ac, char **av, char **envm)
{
	(void)ac;
	(void)av;
	t_mini	shell;
	
	init_mini(&shell,envm);
	while (1)
	{
		shell.rl = readline("minishell> ");
		if (!shell.rl)
			break;
		first_parse(shell.rl, &shell.head);
		parsing(&shell.head, &shell.cmds);
		execute(shell.cmds, &shell, shell.env);
		free_tokens(shell.head);
		free_parser(shell.cmds);
		shell.head = NULL;
		shell.cmds = NULL;
	}
	free(shell.rl);
	return (0);
}
