/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:08:35 by lformank          #+#    #+#             */
/*   Updated: 2024/10/05 15:45:21 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	search_newline(char *storage)
{
	int	i;

	i = 0;
	if (!storage)
		return (-1);
	while (storage[i] != '\0')
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_text_stored(char *scanned)
{
	char	*rest;
	int		index;

	if (!scanned)
		return (NULL);
	index = search_newline(scanned);
	rest = ft_substr(scanned, index + 1, ft_strlen(scanned) - (index + 1));
	if ((int)search_newline(scanned) == -1 || !rest)
	{
		free(scanned);
		scanned = NULL;
		free(rest);
		return (NULL);
	}
	free(scanned);
	scanned = NULL;
	return (rest);
}

char	*ft_print(char *scanned)
{
	char	*print;
	int		index;

	index = 0;
	while (scanned[index] != '\n' && scanned[index] != '\0')
		index++;
	print = ft_substr(scanned, 0, index + 1);
	if (!print)
	{
		free(scanned);
		scanned = NULL;
	}
	return (print);
}

char	*get_text_scanned(int fd, char *stack)
{
	int		coppied;
	int		index;
	char	*buffer;

	index = -1;
	coppied = 1;
	while (stack && index == -1 && coppied != 0)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		coppied = read(fd, buffer, BUFFER_SIZE);
		if (coppied == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (coppied > 0)
			stack = ft_strjoin(stack, buffer);
		free(buffer);
		index = search_newline(stack);
	}
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*print;
	char		*scanned;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	if (!storage)
		storage = (char *)ft_calloc(1, sizeof(char));
	if (!storage)
		return (NULL);
	scanned = get_text_scanned(fd, storage);
	if (!scanned)
	{
		free(storage);
		return (storage = NULL);
	}
	print = ft_print(scanned);
	if (!print)
		return (storage = NULL);
	storage = get_text_stored(scanned);
	return (print);
}

/*int	main(void)
{
	int	fd1;
	int	fd2;
	int	i;
	char *res;

	i = 0;
	fd1 = open("private.txt", O_RDONLY);
	fd2 = open("private.txt", O_RDONLY);
	while (i < 2)
	{
		printf("result1: %s\n", res = get_next_line(fd1));
		free(res);
		i++;
	}
	while (i < 1)
	{
		printf("result2: %s\n", res = get_next_line(fd2));
		free(res);
		i++;
	}
	close (fd1);
	close (fd2);
	return (0);
}*/
