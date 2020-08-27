/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartins <pmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:12:06 by pmartins          #+#    #+#             */
/*   Updated: 2020/08/27 14:12:09 by pmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_and_return_null(char **s)
{
	if (*s && s)
	{
		free(*s);
		*s = NULL;
	}
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int		is_there_line(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		find_char_index(char *s, char c, char d)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == d)
			return (i);
		i++;
	}
	return (-11);
}
