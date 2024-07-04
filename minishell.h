/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:10:03 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/04 09:42:39 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_table
{
	char			**arg;
	char			*token;
	char			*type;
}					t_table;

typedef struct s_token
{
	char *token;
	char *type;
	struct s_token *next;
	struct s_token *prev;
}				t_token;

void ft_lstadd_back(t_token **lst, t_token *new);
char *type(char *p);
t_token *ft_new_token(char *content);
void make_words(char *p, int start, int end, t_token **head);
void split_args(char *p, int start, int inside, t_token **head);
void free_tokens(t_token *head);
void clear_screen();
void first_parse(char *rl, t_token **head);
int parse_quote(char *rl);
char *ft_strtrim(char const *s1, char const *set);
int check_next(char *first, char next);

#endif
