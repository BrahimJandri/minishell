/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:03:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/18 12:33:34 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


t_lexer	*ft_new_token(char *content)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->word = content;
	new_node->token = type(content);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	static int	i;
	t_lexer		*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		i = 0;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->index = ++i;
}

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*begin;
	int			i;

	if (str != NULL)
		s = str;
	if (*s == '\0')
		return (NULL);
	begin = s;
	while (*s)
	{
		i = 0;
		while (delim[i])
		{
			if (*s == delim[i])
			{
				*s = '\0';
				s++;
				return (begin);
			}
			i++;
		}
		s++;
	}
	return (begin);
}


void remove_quotes(char *str)
{
    char *src;
	char *dst;
	
	src = str;
	dst = str;
    while (*src)
    {
        if (*src != '\'' && *src != '"')
        {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int is_n_flag(char *arg)
{
    int i;

    i = 1;
    if (arg[0] != '-')
        return 0;
    while(arg[i] != '\0')
    {
        if (arg[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}
