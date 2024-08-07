/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:01 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/30 10:15:24 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_builtin(char **args)
{
	int	i;

	i = 1;
	if (args[i])
	{
		if (args[i + 1])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			g_global.exit_status = 1;
			return ;
		}
		if (!ft_isdigit(args[i][0]))
		{
			ft_putstr_fd("minishell: exit:  numeric argument required\n", 2);
			g_global.exit_status = 255;
			return ;
		}
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(args[i]));
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}
