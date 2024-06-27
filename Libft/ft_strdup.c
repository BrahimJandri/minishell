/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:18:48 by bjandri           #+#    #+#             */
/*   Updated: 2023/11/22 12:18:49 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	int		len;
	char	*dup;

	i = 0;
	len = ft_strlen(s);
	dup = (char *)malloc(len * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// char str[] = "Hello Duplicate Me";
// printf("%s", ft_strdup(str));

// 	char *str = NULL;
// 	printf("%s", strdup(str));
// }
