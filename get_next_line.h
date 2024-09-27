/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:51:36 by lformank          #+#    #+#             */
/*   Updated: 2024/09/27 14:36:12 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*get_text_stored(int fd, char *stack, char *buffer, char **print);
char	*ft_substr(const char *s, size_t start, size_t len);
char	*ft_strdup(const char *s);
size_t	search_newline(char *storage);
char	*ft_strjoin(char const *s1, char const *s2);
void	putstr(char *s, int len);
char	*ft_calloc(int nmemb, int size);
size_t	ft_strlen(const char *s);
char	*ft_print(char *stack, int index, char **print);
#endif
