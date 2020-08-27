/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartins <pmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:11:12 by pmartins          #+#    #+#             */
/*   Updated: 2020/08/27 14:11:14 by pmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			*ft_calloc(size_t count, size_t size)
{
	void		*ptr2;
	size_t		i;
	char		*ptr1;

	i = 0;
	ptr2 = malloc(count * size);
	ptr1 = ptr2;
	if (ptr1 == NULL)
		return (NULL);
	while (i < (count * size))
	{
		*ptr1 = '\0';
		ptr1++;
		i++;
	}
	return (ptr2);
}

static	char	*ft_substr(char *s, int start, int len)
{
	int			i;
	char		*sub;

	if (len < 0 || !s || start < 0)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (!(sub = ft_calloc((len + 1), sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}

static char		*ft_strjoin(char *s1, char *s2)
{
	char		*new;
	int			len;
	int			i;
	int			j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = ft_calloc((len + 1), sizeof(char))))
		return (NULL);
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[len] = '\0';
	return (new);
}

int				final_step(int fdb, char ***line, char **kpr)
{
	char	*tmp;

	if ((fdb < 0))
	{
		**line = ft_substr(*kpr, 0, ft_strlen(*kpr));
		free_and_return_null(kpr);
		return (0);
	}
	**line = ft_substr(*kpr, 0, fdb);
	tmp = ft_substr(*kpr, (fdb + 1), ft_strlen(*kpr) - (fdb + 1));
	free_and_return_null(kpr);
	*kpr = tmp;
	if (*line)
		return (1);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	char		*buff;
	char		*temp;
	static char	*kpr[OPEN_MAX];
	int			line_exist;
	int			fdb;

	if ((fd < 0) || (read(fd, NULL, 0) < 0) || (BUFFER_SIZE <= 0) || !line)
		return (-1);
	if (!(kpr[fd]) && (!(kpr[fd] = ft_calloc(sizeof(char), (BUFFER_SIZE + 1)))))
		return (-1);
	buff = (char*)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line_exist = is_there_line(kpr[fd]);
	while ((line_exist == 0) && (fdb = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[fdb] = '\0';
		temp = ft_strjoin(kpr[fd], buff);
		free_and_return_null(&kpr[fd]);
		kpr[fd] = temp;
		line_exist = is_there_line(kpr[fd]);
	}
	free_and_return_null(&buff);
	fdb = find_char_index(kpr[fd], '\n', '\0');
	return (final_step(fdb, &line, &kpr[fd]));
}