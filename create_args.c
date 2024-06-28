/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:13:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/28 11:53:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_new_token(char *content)
{
    t_token *new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return NULL;
    new_node->token = content;
    new_node->next = NULL;
    return new_node;
}

void make_words(char *p, int start, int end)
{
    char *word;
    int i;
    t_token *new_word;

    word = (char *)malloc((end - start + 1) * sizeof(char));
    if (!word)
    {
        perror("Failed to allocate memory for word");
        return;
    }

    new_word = (t_token *)malloc(sizeof(t_token));
    if (!new_word)
    {
        perror("Failed to allocate memory for new_word");
        free(word);
        return;
    }
    i = 0;
    while (start < end)
        word[i++] = p[start++];
    word[i] = '\0';
    new_word = ft_new_token(word);
    if (new_word->token)
        printf("ARG: %s\n", new_word->token);
    else
        printf("ARG is NULL\n");
    free(word);
    free(new_word);
}


