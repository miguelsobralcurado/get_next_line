/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:38:54 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/17 09:41:42 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_initialize_struct(t_line *gnl, int fd)
{
	//printf("🐤 1\n");
	gnl->fd = fd;
	gnl->static_buffer = NULL;
	gnl->bytes_read = 0;
	gnl->eof = 0;
}

static char	*read_line(t_line *gnl, char **temp_buffer)
{
	char	*temp;

	//printf("🐤 3\n");
	while (!gnl->static_buffer || !ft_strchr(gnl->static_buffer, '\n'))
	{
		ft_bzero(*temp_buffer, BUFFER_SIZE + 1);
		//printf("🐤 4\n");
		gnl->bytes_read = read(gnl->fd, *temp_buffer, BUFFER_SIZE);
		//printf("🐤 5 bytes_read = %zu\n", gnl->bytes_read);
		if (gnl->bytes_read <= 0)
			break ;
		(*temp_buffer)[gnl->bytes_read] = '\0';
		if (!gnl->static_buffer)
			gnl->static_buffer = ft_strdup(*temp_buffer);
		else
		{
			temp = gnl->static_buffer;
			gnl->static_buffer = ft_strjoin(temp, *temp_buffer);
			free(temp);
		}
		//printf("🐤 6 static_buffer = %s\n", gnl->static_buffer);
	}
	if (!gnl->static_buffer)
		return (free_null(temp_buffer), NULL);
	return (free_null(temp_buffer), gnl->static_buffer);
}

static char	*set_line(t_line *gnl, char *line)
{
	size_t	i;
	char	*temp;

	i = 0;
	//printf("🐤 line = %s line [i](0) = %c\n", line, line[i]);
	while (line[i] && line[i] != '\n')
		i++;
	//printf("🐤 9 line = %s line [i](0) = %u i = %zu\n", line, line[i], i);
	if (line[i] == '\n' && line[i + 1] != '\0')
	{
		temp = ft_substr(line, i + 1, ft_strlen(line + i + 1));
		if (!temp)
			//printf("🐤 10 error line = %s\n", line);	
			return (free_null(&gnl->static_buffer), NULL);
		i++;
		line[i] = '\0';
		//printf("🐤 10 line = %s\n", line);
	}
	else
		temp = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_line	gnl;
	char			*temp_buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1 || gnl.eof == 1)
		return (NULL);
	if (gnl.fd != fd)
	{
		free_null(&gnl.static_buffer);
		ft_initialize_struct(&gnl, fd);
	}
	temp_buffer = ft_calloc(1, BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	//printf("🐤 2\n");
	line = read_line(&gnl, &temp_buffer);
	if (!line)
		//printf("🐤 8\n");
		return (free_null(&gnl.static_buffer), NULL);
	gnl.static_buffer = set_line(&gnl, line);
	if (!gnl.static_buffer && gnl.bytes_read == 0)
		gnl.eof = 1;
	//printf("🐤 12 line = %s\n", line);
	//printf("🐤 13 static_buffer = %s\n", gnl.static_buffer);
	return (line);
}
