/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/30 09:56:55 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_next(char *first, char next)
{
	int	i;

	i = 0;
	while (first[i] && first[i] != next)
		i++;
	return (i);
}

int	parse_qoute(char *rl)
{
	int	i;
	int	j;

	i = 0;
	while (rl[i] == ' ' || rl[i] == '\t' || rl[i] == '\n')
		i++;
	while (rl[i])
	{
		if (rl[i] == '\"' || rl[i] == '\'')
		{
			j = check_next(&rl[i + 1], rl[i]);
			if (rl[i + j + 1] != rl[i])
				return (1);
			i += j + 1;
		}
		i++;
	}
	return (0);
}
char *parse_pipe(char *p)
{
    int i;
    int j;
    char *new_p;
    
    i = 0;
    new_p = NULL;
    while(p[i])
    {
        j = 0;
        if(p[0] == '|' && p[1] == '\0')
            return(p);
        else if(p[i] == '|' && p[i + 1] != '\0' && p[i - 1])
        {
            new_p[j] = p[i];
            new_p[j + 1] = '\0';
            return(new_p);
        }
        i++;
    }
    return (p);
}

void split_args(char *p, int start, int inside)
{
    int end;
    int i;

    i = 0;
    while (p[i])
    {
        if (p[i] == '"')
        {
            inside = !inside;
            i++;
        }
        if (inside || (p[i] != ' ' && p[i] != '\t' && p[i] != '\n' && p[i] != '|'))
            i++;
        else
        {
            if (p[i] == '|')
            {
                if (i > start)
                {
                    end = i;
                    make_words(p, start, end);
                }
                make_words(p, i, i + 1);
                i++;
                start = i;
            }
            else
            {
                end = i;
                make_words(p, start, end);
                while (p[i] == ' ' || p[i] == '\t' || p[i] == '\n')
                    i++;
                start = i;
            }
        }
    }
    if (i > start)
        make_words(p, start, i);
}

void first_parse(char *rl)
{
	int		i;
	int		inside;
	char *trimmed_rl;
	
	i = 0;
	inside = 0;
	
	if (rl && *rl)
		add_history(rl);
	if(ft_strncmp(rl, "clear", 5) == 0)
		rl_clear_display(1,0);
	trimmed_rl = ft_strtrim(rl, " \t\n");
	free(rl);
	if (trimmed_rl[0] == '|' || trimmed_rl[ft_strlen(trimmed_rl) - 1] == '|')
		printf("syntax error near unexpected token `|'\n");
	rl = trimmed_rl;
	split_args(rl, i, inside);
	if (parse_qoute(rl))
		printf("Syntax Error: parsing quote error [KO]\n");
	else
		printf("Syntax Correct [OK]\n");
}

int	main(void)
{
	char	*rl;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break ;
		while(rl[0] == '\0')
			rl = readline("minishell> ");
		first_parse(rl);
	}
	free(rl);
	return (0);
}
