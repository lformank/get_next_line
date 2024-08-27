/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:32:10 by lformank          #+#    #+#             */
/*   Updated: 2024/08/27 15:13:38 by lformank         ###   ########.fr       */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
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

/*int	ft_search_newline(int newline, char *storage)
{

}*/

char	*get_text_stored(int fd, char *storage, char *buffer)
{
	int		n;
	int		printed;
	int		zero;
	int		newline;

	n = 6;
	buffer = 0;
	printed = 0;
	zero = n;
	newline = 0;
	while (zero == n)
	{
		zero = read(fd, buffer, n);
		printed += zero;
		if (zero != 0)
			storage = ft_strjoin(storage, buffer);
//		newline = ft_search_newline(newline, storage);
	}
	free (buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	char	*storage;
	char	*buffer;

	storage = malloc(1 * sizeof(char));
	buffer = malloc(1 * sizeof(char));
	if (!buffer || !storage)
		return (0);
	storage = get_text_stored(fd, storage, buffer);
	return (storage);
}

int	main(void)
{
	int	fd;

	fd = open("private.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
