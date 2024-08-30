/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lformank <lformank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:51:36 by lformank          #+#    #+#             */
/*   Updated: 2024/08/28 12:10:54 by lformank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

#endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
#endif