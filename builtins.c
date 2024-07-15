/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/15 09:53:05 by bjandri          ###   ########.fr       */
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

