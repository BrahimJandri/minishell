/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:03:32 by bjandri           #+#    #+#             */
/*   Updated: 2024/07/30 10:15:09 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	remove_quotes(char *str)
{
	g_global.in_single_quotes = 0;
	g_global.in_double_quotes = 0;
	g_global.src = str;
	g_global.dst = str;
	while (*g_global.src)
	{
		if (*g_global.src == '"' && !g_global.in_single_quotes)
		{
			g_global.in_double_quotes = !g_global.in_double_quotes;
			g_global.src++;
		}
		else if (*g_global.src == '\'' && !g_global.in_double_quotes)
		{
			g_global.in_single_quotes = !g_global.in_single_quotes;
			g_global.src++;
		}
		else if (!g_global.in_single_quotes && !g_global.in_double_quotes
			&& (*g_global.src == '"' || *g_global.src == '\''))
			g_global.src++;
		else
			*g_global.dst++ = *g_global.src++;
	}
	*g_global.dst = '\0';
}

char	*rm_quote(char *str)
{
	int		i;
	int		j;
	char	*dst;

	dst = str;
	j = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i \
				+ 1] == '\''))
			i += 2;
		else
			dst[j++] = str[i++];
	}
	if (j > 0 && (dst[j - 1] == '"' || dst[j - 1] == '\''))
		j--;
	dst[j] = '\0';
	return (str);
}

char	*ft_strnlen(const char *str, char delimiter)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str[i] && str[i] != delimiter)
		i++;
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}
