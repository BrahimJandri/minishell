/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:40:39 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/15 13:11:50 by bjandri          ###   ########.fr       */
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


void cd_builtin(char *rl)
{
    char *home_dir = getenv("HOME");
    char *target_dir = NULL;

    if (rl == NULL)
        target_dir = home_dir;
    else if (ft_strncmp(&rl[3], ".", 1) == 0)
        target_dir = getenv("OLDPWD");
    else 
        target_dir = rl;
    if (chdir(target_dir) != 0)
        perror("cd");
    else 
        setenv("OLDPWD", getcwd(NULL, 0), 1);
}

