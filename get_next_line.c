/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:32:10 by lformank          #+#    #+#             */
/*   Updated: 2024/08/31 18:24:34 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(int nmemb, int size)
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
//	printf("\n%s!!!\n", s1);
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (dest == 0)
		return (0);
	while (s1[i] != '\0')
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		dest[j++] = s2[i++];
	dest[j] = '\0';
//	printf("%s", s2);
	free ((void *)s1);
	return (dest);
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

int	search_newline(char *storage)
{
	int	i;

	i = 0;
	while (i <= BUFFER_SIZE || storage[i] != '\0')
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*save_rest(char *stack, int position)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(stack);
	position++;
	dest = (char *)malloc((len - position) * sizeof(char));
	i = 0;
	while (stack[position] != '\0' && position < len)
	{
		dest[i] = stack[position];
		position++;
		i++;
	}
	free(stack);
	return (dest);
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
	return (ptr);
}

char	*ft_substr(const char *s, unsigned int start, int len)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(s);
	j = 0;
	if (start >= i)
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

char	*get_text_stored(int fd, char *stack, char *buffer)
{
	int		i;
	int		zero;
	int		position;

	i = 0;
	zero = BUFFER_SIZE;
	position = 1;
//	printf("%s.", stack);
	while (zero == BUFFER_SIZE && position != 0)
	{
		zero = read(fd, buffer, BUFFER_SIZE);
		if (zero != 0)
		{
			stack = ft_strjoin(stack, buffer);
			position = search_newline(buffer);
			putstr(stack, position);
			stack = ft_substr(stack, position, ft_strlen(stack));
		}
	}
	free (buffer);
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	static int	x;
	char 		*buffer;

	x = 0;
	if (x == 0)
		storage = (char *)malloc(1 * sizeof(char));
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!storage || !buffer)
		return (0);
//	printf("\n%s__", storage);
	storage = get_text_stored(fd, storage, buffer);
	x++;
	return (storage);
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
//		printf("%s\n!", get_next_line(fd));
		get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}

