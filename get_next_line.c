/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:32:10 by lformank          #+#    #+#             */
/*   Updated: 2024/08/30 15:53:17 by lformank         ###   ########.fr       */
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
	int			i;

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
//	printf("%d,", len);
	position++;
	dest = (char *)malloc((len - position) * sizeof(char));
	i = 0;
	while (stack[position] != '\0' && position < len)
	{
		dest[i] = stack[position];
		position++;
		i++;
//		printf("%s.", dest);
	}
	free(stack);
	printf("\n%s/", dest);
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
	while (zero == BUFFER_SIZE && position != 0)
	{
		zero = read(fd, buffer, BUFFER_SIZE);
		if (zero != 0)
		{
			stack = ft_strjoin(stack, buffer);
			position = search_newline(stack);
			putstr(stack, position);
			stack = save_rest(stack, position);
		}
	}
	free (buffer);
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char	*buffer;

	storage = (char *)malloc(1 * sizeof(char));
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer || !storage)
		return (0);
	storage = get_text_stored(fd, storage, buffer);
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
		printf("%s!", get_next_line(fd));
		i++;
	}
	close(fd);
	return (0);
}

