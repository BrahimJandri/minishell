/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:03:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/23 16:10:44 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	static int i;
	t_lexer	*tmp;

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

int 	is_whitespace(char c)
{
	if(c == 32 || (c >= 9 && c <= 13))
		return 1;
	return 0;
}

char *ft_strtok(char *str, const char *delim)
{
    static char *s;
    char *begin;
    int i;

    if (str != NULL)
        s = str;
    if (*s == '\0')
        return NULL;
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
                return begin;
            }
            i++;
        }
        s++;
    }
    return begin;
}

void remove_quotes(char *str)
{
    char *src;
    char *dst;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    src = str;
    dst = str;
    while (*src)
    {
        if (*src == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
            src++;
        }
        else if (*src == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            src++;
        }
        else if (!in_single_quotes && !in_double_quotes && (*src == '"' || *src == '\''))
            src++;
        else
            *dst++ = *src++;
    }
    *dst = '\0';
}

int is_n_flag(char *arg)
{
    int i = 1;

    if (arg[0] != '-')
        return 0;
    if (arg[1] == '\0')
        return 0;
    while (arg[i] != '\0')
    {
        if (arg[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

void	free_parser(t_parser *head)
{
	t_parser *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

char *rm_quote(char *str)
{
    int i;
    int j;
    char *dst;
    

    dst = str;
    j = 0;
    i = 0;
    while (str[i])
    {
        if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i + 1] == '\''))
            i += 2;
        else
            dst[j++] = str[i++];
    }
    if(j > 0 && (dst[j - 1] == '"' || dst[j - 1] == '\''))
        j--;
    dst[j] = '\0';
    return str;
}
