/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:10:03 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/28 08:45:22 by bjandri          ###   ########.fr       */
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
	char			*arg;
	char			*token;
	char			*type;
	struct s_table	*next;
}					t_table;

void				split_args(char *p, int start, int inside);
int					parse_qoute(char *rl);
int					check_next(char *first, char next);
void				make_words(char *p, int start, int end);

#endif
