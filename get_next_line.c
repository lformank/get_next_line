/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:08:35 by lformank          #+#    #+#             */
/*   Updated: 2024/09/27 09:25:06 by lformank         ###   ########.fr       */
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

char	*ft_print(char *stack, int index, char **pprint)
{
	char	*print;
	char	*storage;

	storage = 0;
	storage = ft_strdup(stack);
	print = ft_substr(stack, 0, index + 1);
	*pprint = print;
	stack = ft_substr(storage, index + 1, ft_strlen(stack) - (index + 1));
	index = search_newline(stack);
	return (stack);
}

char	*get_text_stored(int fd, char *stack, char *buffer, char **pprint)
{
	int		coppied;
	int		index;
	char	*print;

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
		stack = ft_print(stack, index, pprint);
		break ;
	}
	if (coppied == 0)
	{
		print = ft_strdup(stack);
		*pprint = print;
	}
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*pprint;
	char		*stack;

	pprint = 0;
	buffer = 0;
	if (!buffer)
		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(storage);
		return (0);
	}
	if (!storage)
		storage = (char *)ft_calloc(1, sizeof(char));
	if (!storage || !buffer)
		return (0);
	stack = get_text_stored(fd, storage, buffer, &pprint);
	storage = ft_strdup(stack);
	free (buffer);
	free (stack);
	return (pprint);
}

/*int	main(void)
{
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	fd = open("private.txt", O_RDONLY);
	while (i < 3)
	{
		printf("result: %s", get_next_line(fd));
		i++;
	}
	close (fd);
	return (0);
}*/
