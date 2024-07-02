/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:09:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/02 12:42:17 by bjandri          ###   ########.fr       */
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

void    ft_lstadd_back(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}

char    *type(char *p)
{
    if(p[0] == '|')
        return("PIPE");
    else if(p[0] == '>' && p[1] != '>')
        return("RED_OUT");
    else if(p[0] == '<' && p[1] != '<')
        return("RED_INP");
    else if(p[0] == '<' && p[1] == '<')
        return("APP_RED_INP");
    else if(p[0] == '>' && p[1] == '>')
        return("APP_RED_OUT");
    else
        return("ARG");
}

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


void make_words(char *p, int start, int end, t_token **head)
{
    char *word;
    int i;

    word = (char *)malloc((end - start + 1) * sizeof(char));
    if (!word)
    {
        perror("Failed to allocate memory for word");
        return;
    }
    i = 0;
    while (start < end)
        word[i++] = p[start++];
    word[i] = '\0';
    ft_lstadd_back(head, ft_new_token(word));
}

void split_args(char *p, int start, int inside, t_token **head)
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
                    make_words(p, start, end, head);
                }
                make_words(p, i, i + 1, head);
                i++;
                while (p[i] == ' ' || p[i] == '\t' || p[i] == '\n')
                    i++;
                start = i;
            }
            else
            {
                end = i;
                make_words(p, start, end, head);
                while (p[i] == ' ' || p[i] == '\t' || p[i] == '\n')
                    i++;
                start = i;
            }
        }
    }
    if (i > start)
        make_words(p, start, i, head);
}

void clear_screen() {
    printf("\033[H\033[J");
}

void first_parse(char *rl, t_token **head)
{
	int		i;
	int		inside;
	char *trimmed_rl;
	
	i = 0;
	inside = 0;
	add_history(rl);
	if(ft_strncmp(rl, "clear", 5) == 0)
		clear_screen();
	trimmed_rl = ft_strtrim(rl, " \t\n");
	free(rl);
	if (trimmed_rl[0] == '|' || trimmed_rl[ft_strlen(trimmed_rl) - 1] == '|')
    {
		printf("syntax error near unexpected token |'\n");
        rl = readline("minishell> ");    
    }
	rl = trimmed_rl;
	if (parse_qoute(rl))
    {
		printf("Syntax Error: parsing quote error [KO]\n");
        rl = readline("minishell> ");       
    }
	else
		printf("Syntax Correct [OK]\n");
	split_args(rl, i, inside, head);
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


int	main(void)
{
	char	*rl;
    t_token *head;
    t_token *tmp;
    
    head = NULL;
	while (1)
	{
		rl = readline("minishell> ");
		if (!rl)
			break ;
		while(rl[0] == '\0')
			rl = readline("minishell> ");
		first_parse(rl, &head);
        tmp = head;
        while (tmp)
        {
            printf("[TOKEN = %s] == [TYPE = %s]\n", tmp->token, tmp->type);
            tmp = tmp->next;   
        }
        free_tokens(head);
        head = NULL;
	}
	free(rl);
	return (0);
}

