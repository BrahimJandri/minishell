/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/24 15:19:55 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_next(char *first, char next)
{
    int i;

    i = 0;
    while(first[i] && first[i] != next)
        i++;
    return (i);
}

int    parse_qoute(char *rl)
{
    int i;
    int j;

    i = 0;
    while(rl[i] == ' ' || rl[i] == '\t' || rl[i] == '\n')
        i++;
    while (rl[i])
    {
        if(rl[i] == '\"' || rl[i] == '\'')
        {
            j = check_next(&rl[i + 1], rl[i]);
            if(rl[i + j + 1] != rl[i])
                return (1);
            i += j + 1;
        }
        i++;
    }
    return(0);
}

void split_args(char *rl)
{
    int i;
    int inside;
    int len;

    len = ft_strlen(rl);
    if(rl[0] == '|' || rl[len -1] == '|')
        printf("syntax error near unexpected token `|'\n");
    inside = 0;
    i = 0;
    if(rl == NULL)
        return ;
    while(rl[i] == ' ' || rl[i] == '\t' || rl[i] == '\n')
        i++;
    while (rl[i])
    {
        if(rl[i] == '\"')
            inside = 1;
        else if(rl[i] == ' ' && !inside)
            write(1, "\n", 1);
        else
            write(1, &rl[i], 1);
        i++;
    }
    write(1, "\n", 1);    
}

int main(void)
{
    char *rl;
    while(1)
    {
        rl = readline("minishell >");
        if (rl && *rl)
            add_history(rl);
        split_args(rl);
        if (parse_qoute(rl))
            printf("Syntax Error: parsing quote error [KO]\n");
        else
            printf("%s [OK]\n", rl);
    }
    return (0);
}
