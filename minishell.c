/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/28 16:16:36 by bjandri          ###   ########.fr       */
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

void	split_args(char *p, int start, int inside)
{
	int	end;
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] == '"')
		{
			inside = !inside;
			i++;
		}
		if (inside || (p[i] != ' ' && p[i] != '\t' && p[i] != '\n'))
			i++;
		else
		{
			end = i;
			make_words(p, start, end);
			while (p[i] == ' ' || p[i] == '\t' || p[i] == '\n')
				i++;
			start = i;
		}
	}
	make_words(p, start, i);
}

int	main(void)
{
	char	*rl;
	int		i;
	int		inside;

	i = 0;
	inside = 0;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break ;
		if (rl && *rl)
			add_history(rl);
		if(ft_strncmp(rl, "clear", 5) == 0)
			rl_clear_display(1,0);
		if (rl[0] == '|' || rl[ft_strlen(rl) - 1] == '|')
			printf("syntax error near unexpected token `|'\n");
		while (rl[i] == ' ' || rl[i] == '\t' || rl[i] == '\n')
			i++;
		split_args(rl, i, inside);
		if (parse_qoute(rl))
			printf("Syntax Error: parsing quote error [KO]\n");
		else
			printf("Syntax Correct [OK]\n");
	}
	return (0);
}
