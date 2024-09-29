/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:08:35 by lformank          #+#    #+#             */
/*   Updated: 2024/09/29 11:35:10 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	search_newline(char *storage)
{
	int	i;

	i = 0;
	while (storage[i] != '\0')
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_print(char *stack, int index, char **print)
{
	char	*storage;
	char	*rest;

	rest = 0;
	storage = 0;
	storage = ft_strdup(stack);
	*print = ft_substr(stack, 0, index + 1);
	rest = ft_substr(storage, index + 1, ft_strlen(storage) - (index + 1));
	free(storage);
	free(stack);
	index = search_newline(rest);
	return (rest);
}

char	*get_text_stored(int fd, char *stack, char *buffer, char **print, int *flag)
{
	int		coppied;
	int		index;

	index = search_newline(stack);
	coppied = 1;
	while (index == -1 && coppied != 0)
	{
		coppied = read(fd, buffer, BUFFER_SIZE);
		if (coppied != 0)
			stack = ft_strjoin(stack, buffer);
		index = search_newline(stack);
	}
	while (index != -1 && stack != NULL && coppied != 0)
	{
		stack = ft_print(stack, index, print);
		break;
	}
	if (coppied == 0 && *flag != 1)
	{
		*print = ft_substr(stack, 0, ft_strlen(stack));
		*flag = 1;
	}
	printf("flag: %d", *flag);
	free(buffer);
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*print;
	static int	*flag;

	print = 0;
	if (!flag)
		flag = (int *)ft_calloc(1, sizeof(int));
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(storage);
		return (0);
	}
	if (!storage)
		storage = (char *)ft_calloc(1, sizeof(char));
	if (!storage || !buffer || !flag)
		return (0);
	if (*flag != 1)
	{
		storage = get_text_stored(fd, storage, buffer, &print, flag);
		return (print);
	}
	free (print);
	printf("print: %s", print);
	free (flag);
	free (buffer);
	return (NULL);
}

int	main(void)
{
	int	fd;
	int	i;
	char *res;

	i = 0;
	fd = 0;
	fd = open("private.txt", O_RDONLY);
	while (i < 6)
	{
		printf("result: %s", res = get_next_line(fd));
		free(res);
		i++;
	}
	close (fd);
	return (0);
}
