/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:10:03 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/02 11:28:49 by bjandri          ###   ########.fr       */
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

t_token				*ft_new_token(char *content);
void 				first_parse(char *rl, t_token **head);
int					parse_qoute(char *rl);
int					check_next(char *first, char next);
void				make_words(char *p, int start, int end, t_token **head);

#endif
