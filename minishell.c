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
void split_args(char *p)
{
    int start = 0;
    int end = 0;
    int inside = 0;
    int i = 0;

    while (p[i] == ' ' || p[i] == '\t' || p[i] == '\n')
        i++;
    start = i;
    while (p[i])
    {
        if (p[i] == '"')
        {
            inside = !inside;
            i++;
            continue;
        }
        if (inside || (p[i] != ' ' && p[i] != '\t' && p[i] != '\n'))
            i++;
        else
        {
            end = i;
            while (start < end)
            {
                printf("%c", p[start]);
                start++;
            }
            printf("\n");
            while (p[i] == ' ' || p[i] == '\t' || p[i] == '\n')
                i++;
            start = i;
        }
    }
    while (start < i)
    {
        printf("%c", p[start]);
        start++;
    }
    printf("\n");
}

int main(void)
{
    char *rl;
    while(1)
    {
        rl = readline("minishell >");
        if (rl && *rl)
            add_history(rl);
        if(rl[0] == '|' || rl[ft_strlen(rl) -1] == '|')
            printf("syntax error near unexpected token `|'\n");
        split_args(rl);
        if (parse_qoute(rl))
            printf("Syntax Error: parsing quote error [KO]\n");
        else
            printf("%s [OK]\n", rl);
    }
    return (0);
}
