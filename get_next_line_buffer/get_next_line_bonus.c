/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:16 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/18 17:38:16 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (!buffer[fd][0])
		{
			bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytes_read < 0)
				return (clear_buffer(buffer[fd]), free(line), NULL);
			if (bytes_read == 0)
				break ;
			buffer[fd][bytes_read] = '\0';
		}
		line = gnl_strjoin(line, buffer[fd]);
		if (!line)
			return (clear_buffer(buffer[fd]), NULL);
		if (gnl_strchr(buffer[fd], '\n'))
			break ;
	}
	return (line);
}
