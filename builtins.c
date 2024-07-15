/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/15 15:45:55 by bjandri          ###   ########.fr       */
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
    if (args[i] && !ft_strncmp(args[i], "-n", 2))
    {
        n_flag = 1;
        i++;
    }
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!n_flag)
        write(1, "\n", 1);
}
