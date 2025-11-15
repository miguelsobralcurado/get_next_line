/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:38:54 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/15 16:03:27 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_initialize_struct(t_line *gnl, int fd)
{
	//printf("🐤 1\n");
	gnl->fd = fd;
	gnl->stash = NULL;
	gnl->bytes_read = 0;
}

static char	*read_line(t_line *gnl, char **buffer)
{
	char	*temp;

	//printf("🐤 3\n");
	while (!gnl->stash || !ft_strchr(gnl->stash, '\n'))
	{
		ft_bzero(*buffer, BUFFER_SIZE + 1);
		//printf("🐤 4\n");
		gnl->bytes_read = read(gnl->fd, *buffer, BUFFER_SIZE);
		//printf("🐤 5 bytes_read = %zu\n", gnl->bytes_read);
		if (gnl->bytes_read <= 0)
			break ;
		*buffer[gnl->bytes_read] = '\0';
		if (!gnl->stash)
			gnl->stash = ft_strdup(*buffer);
		else
		{
			temp = gnl->stash;
			gnl->stash = ft_strjoin(temp, *buffer);
			free_null(&temp);
		}
		//printf("🐤 6 stash = %s\n", gnl->stash);
	}
	if (!gnl->stash)
		return (free_null(buffer), NULL);
	return (free_null(buffer), gnl->stash);
}

static char	*set_line(t_line *gnl, char *line)
{
	size_t	new_line;
	char	*temp;

	new_line = 0;
	//printf("🐤 line = %s line [new_line](0) = %c\n", line, line[new_line]);
	while (line[new_line] && line[new_line] != '\n')
		new_line++;
	//printf("🐤 9 line = %s line [new_line](0) = %u new_line = %zu\n", line, line[new_line], new_line);
	temp = ft_substr(line, new_line + 1, ft_strlen(line) - (new_line + 1));
	if (!temp)
	{
		//printf("🐤 10 error line = %s\n", line);	
		return (free(gnl->stash), free_null(&line), NULL);
	}
//	line[new_line + 1] = '\0';
	//printf("🐤 10 line = %s\n", line);	
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_line	gnl;
	char			*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1 || gnl.bytes_read < 0)
		return (NULL);
	if (gnl.fd != fd)
		ft_initialize_struct(&gnl, fd);
	buffer = ft_calloc(1, BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	//printf("🐤 2\n");
	line = read_line(&gnl, &buffer);
	if (!line || gnl.bytes_read < 0)
	{
		//printf("🐤 8\n");
		if (gnl.stash)
			free_null(&gnl.stash);
		return (NULL);
	}
	gnl.stash = set_line(&gnl, line);
	if (gnl.bytes_read == 0)
		gnl.bytes_read = -1;
	//printf("🐤 12 line = %s\n", line);
	//printf("🐤 13 stash = %s\n", gnl.stash);
	return (line);
}
