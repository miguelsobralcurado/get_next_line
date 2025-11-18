/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:09:41 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/18 16:38:12 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (clear_buffer(buffer), NULL);
	line = NULL;
	while (1)
	{
		if (!buffer[0])
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
				return (clear_buffer(buffer), free(line), NULL);
			if (bytes_read == 0)
				break ;
			buffer[bytes_read] = '\0';
		}
		line = gnl_strjoin(line, buffer);
		if (!line)
			return (clear_buffer(buffer), NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}
