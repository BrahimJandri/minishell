/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:52:33 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/30 09:53:08 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (arg[1] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_builtin(char **args)
{
	int	i;
	int	n_flag;

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
