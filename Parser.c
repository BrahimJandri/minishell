/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:37:44 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/06 09:27:16 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    type(char *p)
{    
    if(ft_strncmp(p, "|", ft_strlen(p)) == 0)
        return(1);
    else if(ft_strncmp(p, ">", ft_strlen(p)) == 0)
        return(2);
    else if(ft_strncmp(p, "<", ft_strlen(p)) == 0)
        return(3);
    else if(ft_strncmp(p, "<<", ft_strlen(p)) == 0)
        return(4);
    else if(ft_strncmp(p, ">>", ft_strlen(p)) == 0)
        return(5);
    else
        return(6);
}

int check_next(char *first, char next)
{
    int i = 0;
    while (first[i] && first[i] != next)
        i++;
    return i;
}

int parse_quote(char *rl)
{
    int i = 0;
    int j;

    while (rl[i] == ' ' || rl[i] == '\t' || rl[i] == '\n')
        i++;
    while (rl[i])
    {
        if (rl[i] == '"' || rl[i] == '\'') {
            j = check_next(&rl[i + 1], rl[i]);
            if (rl[i + j + 1] != rl[i])
                return 1;
            i += j + 1;
        }
        i++;
    }
    return 0;
}

void clear_screen()
{
    printf("\033[H\033[J");
}

void first_parse(char *rl, t_token **head)
{
    int i = 0;
    int inside = 0;
    char *trimmed_rl;

    add_history(rl);
    if (ft_strncmp(rl, "clear", 5) == 0)
        clear_screen();
    trimmed_rl = ft_strtrim(rl, " \t\n");
    free(rl);
    if (trimmed_rl[0] == '|' || trimmed_rl[strlen(trimmed_rl) - 1] == '|')
        perror("syntax error near unexpected token '|'\n");
    rl = trimmed_rl;
    if (parse_quote(rl))
        perror("Syntax Error: parsing quote error [KO]\n");
    split_args(rl, i, inside, head);
}

