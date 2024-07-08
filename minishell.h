/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachid <rachid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:10:03 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/07 18:54:13 by rachid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum s_tokens
{
	PIPE = 1,
	RED_OUT = 2,
	RED_IN = 3,
	HERDOC = 4,
	APP_OUT = 5,
	ARG = 6,
}					t_tokens;

typedef struct s_lexer
{
	char			*token;
	t_tokens		type;
	int 			index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

t_lexer				*ft_new_token(char *content);
void				ft_lstadd_back(t_lexer **lst, t_lexer *new);
int					type(char *p);
void				make_words(char *p, int start, int end, t_lexer **head);
void				split_args(char *p, int start, int inside, t_lexer **head);
void				free_tokens(t_lexer *head);
void				clear_screen(void);
void				first_parse(char *rl, t_lexer **head);
int					parse_quote(char *rl);
char				*ft_strtrim(char const *s1, char const *set);
int					check_next(char *first, char next);
int 				is_whitespace(char c);

#endif
