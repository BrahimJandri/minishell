/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:10:03 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/29 12:44:55 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>


typedef struct s_global
{
	int		exit_status;
	char 	*key;
    char 	*value;
    char 	*equal_sign_pos;
    char 	*plus_equal_sign_pos;
	int		end;
	char	quote;
}				t_global;

extern t_global global;

typedef enum s_builtins{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	EXIT,
	ENV,
}			e_builtins;

typedef enum s_tokens
{
	PIPE = 1,
	RED_OUT,
	RED_IN,
	HERDOC,
	APP_OUT,
	ARG,
}					e_tokens;

typedef struct s_lexer
{
	char			*word;
	e_tokens		token;
	int 			index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*pwd;
	char			*oldpwd;
	struct s_env	*next;
}					t_env;

typedef struct s_parser
{
	char 		**str;
	int 		n_redirections;
	t_lexer 	*redirections;
	e_builtins	builtin;
	struct s_parser *next;
	struct s_parser *prev;
}				t_parser;

typedef struct s_mini
{
	int			pipes;
	char 		**envp;
	char 		**path;
	char		*rl;
	t_env		*env;
	t_parser 	*cmds;
	t_lexer 	*head;
	
}				t_mini;

/***************************** JANDRI **********************************/
t_lexer				*ft_new_token(char *content);
void				ft_lstadd_back(t_lexer **lst, t_lexer *new);
char				*ft_strtrim(char const *s1, char const *set);
int 				is_whitespace(char c);
char 				*ft_strtok(char *str, const char *delim);
void				free_parser(t_parser *head);
void 				remove_quotes(char *str);
int 				is_n_flag(char *arg);
char 				*rm_quote(char *str);
void				ft_lstadd(t_env **lst, t_env *new);
char 				*ft_strnlen(const char *str, char delimiter);

/***************************** execution **********************************/
void				pipe_execution(t_parser *cmds, t_mini *shell);
int					pipe_check(char **args);
void				execute_command(char *command, char **args, t_mini *shell);
void				redirection_execution(t_parser *cmds, t_mini *shell);
void				execute_builtin(t_parser *args, t_env **env);
void 				execute(t_parser *parser, t_mini *shell, t_env **env);

/***************************** Lexer *************************************/
void				make_words(char *p, int start, int end, t_lexer **head);
void				step_one(char *p, int *inside, char *quote, int i);
void				split_args(char *p, int start, int inside, t_lexer **head);
void				free_tokens(t_lexer *head);

/***************************** Parser **********************************/
int					type(char *p);
int					check_next(char *first, char next);
int					parse_quote(char *rl);
void				clear_screen(void);
void				first_parse(char *rl, t_lexer **head);


/***************************** builtins **********************************/
void 				cd_builtin(char **args, t_env **env);
void 				echo_builtin(char **args);
t_env				*create_env(char **env);
char 				*getenv_value(t_env *env, const char *key);
t_env 				*ft_new_env(const char *key, const char *value);
void 				update_env(t_env **env, const char *key, const char *value);
void 				env_builtin(t_env **env);
void 				exit_builtin(char **args);
int 				count_env(t_env *env);
void 				swap_env(t_env **a, t_env **b);
void 				sort_env(t_env **env_array, int count);
void    			print_sorted(t_env **env_array, int count);
void 				sorted_env(t_env **env);
int 				is_valid_identifier(const char *str);
void 				handle_assignment(char *arg, t_env **env);
void 				process_arg(char *arg, t_env **env);
void 				export_builtin(char **args, t_env **env);
int 				pwd_builtin(void);
void 				unsetenv_custom(t_env **env, const char *key);
void 				unset_builtin(char **args, t_env **env);

/**************             DAMSSI             *************/

void 				parsing(t_lexer **head, t_parser **commands);
void				cmd_addback(t_parser **command, t_parser *new_cmd);
t_parser 			*new_cmd(char **cmd);
int 				find_builtin(char *first_word);
void 				argscpy(t_lexer **head, int args, char **cmd);
void 				rm_node(t_lexer **lst);
int 				count_args(t_lexer **lst);
void 				rm_redirection(t_lexer **head, t_parser **cmd);
void 				add_redirection(t_lexer *lst, t_parser **cmd);
void    			lex_addback(t_lexer **redirections, t_lexer *new_lex);
t_lexer     		*new_lex(int r_num, e_tokens redirection, char *file);
e_tokens    		red_join(e_tokens r1, e_tokens r2);
int     			redir_kind(t_lexer *lst);
void 				ft_error(char *message);
int 				redirection_check(t_lexer *tmp);
char			 	**arr_dup(char **envm);



#endif
