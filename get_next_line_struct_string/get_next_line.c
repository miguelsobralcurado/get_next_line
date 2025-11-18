/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:38:54 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/18 10:24:58 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_initialize_struct(t_line *gnl, int fd)
{
	gnl->fd = fd;
	gnl->static_buffer = NULL;
	gnl->bytes_read = 0;
	gnl->eof = 0;
}

static char	*read_line(t_line *gnl, char **temp_buffer)
{
	char	*temp;

	while (!gnl->static_buffer || !ft_strchr(gnl->static_buffer, '\n'))
	{
		ft_bzero(*temp_buffer, BUFFER_SIZE + 1);
		gnl->bytes_read = read(gnl->fd, *temp_buffer, BUFFER_SIZE);
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
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n' && line[i + 1] != '\0')
	{
		temp = ft_substr(line, i + 1, ft_strlen(line + i + 1));
		if (!temp)
			return (free_null(&gnl->static_buffer), NULL);
		i++;
		line[i] = '\0';
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
	line = read_line(&gnl, &temp_buffer);
	if (!line)
		return (free_null(&gnl.static_buffer), NULL);
	gnl.static_buffer = set_line(&gnl, line);
	if (!gnl.static_buffer && gnl.bytes_read == 0)
		gnl.eof = 1;
	return (line);
}
