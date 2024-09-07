/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_old.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:32:10 by lformank          #+#    #+#             */
/*   Updated: 2024/09/07 14:55:02 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
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

void	putstr(char *s, int len)
{
	int	i;

	i = 0;
	while (i <= len || s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
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
	free ((void *)s1);
	free ((void *)s2);
	return (dest);
}

int	search_newline(char *storage)
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
	int		i;

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
	free ((void *)s);
	return (ptr);
}

char	*ft_substr(const char *s, unsigned int start, int len)
{
	char				*dest;
	unsigned int		j;

	j = 0;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (0);
	while (j < (unsigned int)len)
	{
		dest[j] = s[j + start];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*get_text_stored(int fd, char *stack, char *buffer, char **pprint)
{
	int		zero;
	int		position;
	char	*print;
	char	*storage;

	zero = BUFFER_SIZE;
	position = 1;
	storage = 0;
	print = 0;
	while (zero == BUFFER_SIZE && position != 0)
	{
		zero = read(fd, buffer, BUFFER_SIZE);
		stack = ft_strjoin(stack, buffer);
		position = search_newline(stack);
		if (zero <= BUFFER_SIZE && zero != 0)
		{
			print = ft_substr(stack, 0, position + 1);
			*pprint = print;
			storage = ft_substr(stack, position + 1, ft_strlen(stack) - (position + 1));
			free (stack);
			return (storage);
		}
		else if (zero == 0 || position == -1)
		{
			*pprint = stack;
			position = 0;
			free (storage);
			return (NULL);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char 		*buffer;
	char		*pprint;
	char		*stack;

	pprint = 0;
	free (pprint);
	buffer = (char *)malloc((BUFFER_SIZE + 1)* sizeof(char));
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
	storage = stack;
	return (pprint);
}

int	main(void)
{
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	fd = open("private.txt", O_RDONLY);
	while (i < 12)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close (fd);
	return (0);
}

