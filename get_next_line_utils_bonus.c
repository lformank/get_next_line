/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:33:38 by lformank          #+#    #+#             */
/*   Updated: 2024/10/05 15:09:30 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	free ((void *)s1);
	return (dest);
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
		return (NULL);
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
