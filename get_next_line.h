/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:10:41 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/18 15:08:14 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// get_next_line
char	*get_next_line(int fd);

// utils
void	clear_buffer(char *buffer);
size_t	gnl_strlen(const char *s);
int		gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

#endif