/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:37:11 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/29 12:12:25 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_words(char *p, int start, int end, t_lexer **head)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
	{
		printf("Failed to allocate memory for word");
		return ;
	}
	while (start < end)
		word[i++] = p[start++];
	word[i] = '\0';
	ft_lstadd_back(head, ft_new_token(word));
}


void	step_one(char *p, int *inside, char *quote, int i)
{
	(void)inside;
	if (*quote == 0)
	{
		*quote = p[i];
		*inside = 1;
	}
	else if (*quote == p[i])
	{
		*quote = 0;
		*inside = 0;
	}
}

void	split_args(char *p, int start, int inside, t_lexer **head)
{
	int		i;

	i = 0;
	global.end = 0;
	rm_quote(p);
	while (p[i])
	{
		if (p[i] == '"' || p[i] == '\'')
			step_one(p, &inside, &global.quote, i++);
		else if (!inside && (is_whitespace(p[i]) || p[i] == '|' || p[i] == '>' || p[i] == '<'))
		{
			global.end = i;
			if (global.end > start)
				make_words(p, start, global.end, head);
			if (p[i] == '|' || p[i] == '>' || p[i] == '<')
				make_words(p, i, i + 1, head);
			while (is_whitespace(p[++i]));
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		make_words(p, start, i, head);
}


void	free_tokens(t_lexer *head)
{
	t_lexer	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->word);
		free(tmp);
	}
}
