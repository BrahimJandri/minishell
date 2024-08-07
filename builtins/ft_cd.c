/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:11 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/28 10:57:49 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(char **args, t_env **env)
{
	char	*path;
	char	*oldpwd;

	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return ;
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
