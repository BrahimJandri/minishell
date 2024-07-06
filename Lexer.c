/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:37:11 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/06 09:41:26 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token *ft_new_token(char *content)
{
    t_token *new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return NULL;

    new_node->token = content;
    new_node->type = type(content);
    new_node->next = NULL;
    new_node->prev = NULL; 
    return new_node;
}

void ft_lstadd_back(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!new)
        return;
    if (!*lst) {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}


void make_words(char *p, int start, int end, t_token **head)
{
    char *word;
    int i;

    word = (char *)malloc((end - start + 1) * sizeof(char));
    if (!word) {
        perror("Failed to allocate memory for word");
        return;
    }
    i = 0;
    while (start < end)
        word[i++] = p[start++];
    word[i] = '\0';
    ft_lstadd_back(head, ft_new_token(word));
}
void step_one(char *p, int inside, int quote, int i)
{
    if (quote == 0)
    {
        quote = p[i];
        inside = 1;
    }
    else if (quote == p[i])
    {
        quote = 0;
        inside = 0;
    }
}


void split_args(char *p, int start, int inside, t_token **head)
{
    int end;
    int i;
    char quote;
    
    i = 0;
    quote = 0;
    while (p[i])
    {
        if (p[i] == '"' || p[i] == '\'')
        {
            step_one(p, inside, quote, i);
            i++;
        }
        else if (!inside && (p[i] == ' ' || p[i] == '\t' || p[i] == '\n' || p[i] == '|'))
        {
            end = i;
            if (end > start)
                make_words(p, start, end, head);
            if (p[i] == '|')
                make_words(p, i, i + 1, head);
            while (p[++i] == ' ' || p[i] == '\t' || p[i] == '\n');
            start = i;
        }
        else
            i++;
    }
    if (i > start)
        make_words(p, start, i, head);
}

void free_tokens(t_token *head)
{
    t_token *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->token);
        free(tmp);
    }
}
