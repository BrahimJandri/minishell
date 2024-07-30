/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:21 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/30 10:15:55 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(const char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	handle_assignment(char *arg, t_env **env)
{
	char	*existing_value;
	char	*new_value_part;

	if (g_global.plus_equal_sign_pos)
	{
		g_global.key = ft_substr(arg, 0, g_global.plus_equal_sign_pos - arg);
		existing_value = getenv_value(*env, g_global.key);
		new_value_part = ft_strdup(g_global.plus_equal_sign_pos + 2);
		if (existing_value)
			g_global.value = ft_strjoin(existing_value, new_value_part);
		else
			g_global.value = ft_strdup(new_value_part);
	}
	else
	{
		g_global.key = ft_substr(arg, 0, g_global.equal_sign_pos - arg);
		g_global.value = ft_strdup(g_global.equal_sign_pos + 1);
	}
}

void	process_arg(char *arg, t_env **env)
{
	remove_quotes(arg);
	g_global.equal_sign_pos = ft_strchr(arg, '=');
	g_global.plus_equal_sign_pos = strstr(arg, "+=");
	if (g_global.equal_sign_pos || g_global.plus_equal_sign_pos)
		handle_assignment(arg, env);
	else
	{
		g_global.key = ft_strdup(arg);
		g_global.value = NULL;
	}
	if (!is_valid_identifier(g_global.key))
	{
		ft_putendl_fd("minishell: export: not a valid identifier", 2);
		free(g_global.key);
		if (g_global.value)
			free(g_global.value);
		return ;
	}
	update_env(env, g_global.key, g_global.value);
	free(g_global.key);
	if (g_global.value)
		free(g_global.value);
}

void	export_builtin(char **args, t_env **env)
{
	int	i;

	if (!args[1])
	{
		sorted_env(env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		process_arg(args[i], env);
		i++;
	}
}
