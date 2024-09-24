/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:08:35 by lformank          #+#    #+#             */
/*   Updated: 2024/09/24 17:12:43 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_calloc(int nmemb, int size)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = 0;
	ptr = (char *)malloc(nmemb * size);
	if (ptr == 0)
		return (0);
	while (i < nmemb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;

	dest = 0;
	i = 0;
	j = 0;
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (dest == 0)
		return (0);
	while (s1[i] != '\0')
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}

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

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*dest;
	size_t	j;

	j = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) + start))
		len = (ft_strlen(s) + start);
	dest = ft_calloc((int)len + 1, sizeof(char));
	if (!dest)
		return (0);
	while (j < len)
	{
		dest[j] = s[j + start];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*get_text_stored(int fd, char *stack, char *buffer, char **pprint)
{
	int		coppied;
	int		index;
	char	*print;
	char	*storage;

	index = -1;
	storage = 0;
	coppied = 1;
	while (index == -1 && coppied != 0)
	{
		coppied = read(fd, buffer, BUFFER_SIZE);
//		printf("\ncoppied: %d", coppied);
		stack = ft_strjoin(stack, buffer);
//		printf("\nstack: %s", stack);
		index = search_newline(stack);
//		printf("\nindex: %d", index);
	}
	while (index != -1 && stack != NULL)
	{
		print = ft_substr(stack, 0, index + 1);
//		printf("\nprint: %s", print);
		*pprint = print;
		stack = ft_substr(stack, index + 1, ft_strlen(stack) - (index + 1));
		index = search_newline(stack);
//		printf("\nstack: %s", stack);
	}
	free (stack);
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char 		*buffer;
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
//	printf("\nstorage: %s", storage);
	free (buffer);
	free (stack);
	return (pprint);
}

int	main(void)
{
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	fd = open("private.txt", O_RDONLY);
	while (i < 2)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close (fd);
	return (0);
}