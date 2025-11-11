/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:38:54 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/11 18:11:14 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

typedef struct	new_line
{
	char		*buffer;
	ssize_t		n;
	size_t		total_size;
	size_t		start;
	size_t		end;
	int			fd;
}				t_line;

void	ft_initialize_struct(t_line *nl, int fd)
{
	if (!nl->buffer)
	{
		nl->buffer = malloc(BUFFER_SIZE);
		if (!nl->buffer)
			return (NULL);
	}
	if (!nl->fd)
		nl->fd = fd;
	if (!nl->total_size)
		nl->total_size = 0;
	if (!nl->start)
		nl->start = 0;
	if (!nl->n)
		nl->n = read(nl->fd, nl->buffer + nl->total_size, BUFFER_SIZE);
}

char	*new_string(t_line *nl)
{
	char	*temp;
	
	nl->end = nl->start;
	while (nl->buffer[nl->start + nl->end] && nl->buffer[nl->start + nl->end] != '\n')
		nl->end++;
	temp = ft_substr(nl->buffer, nl->start, nl->end - nl->start + 1);
	if (nl->buffer[nl->start + nl->end] != '\n')
	{
//		ft_re_read(fd, nl->buffer, &total_size, &nl->start, &nl->end);
		nl->n = read(nl->fd, nl->buffer + nl->total_size, BUFFER_SIZE);
		nl->total_size += nl->n;
		nl->start = nl->end;
		temp = ft_strjoin(temp, new_string(nl));
		if (!temp)
			return (NULL);
	}
	if (nl->buffer[nl->start] == '\n')
		nl->start++;
}

char	*get_next_line(int fd)
{
	static t_line	*nl;
	char			*temp;

	if (!fd)
		return (NULL);
	if (!nl)
	{
		nl = (t_line *)malloc(sizeof(t_line *));
		if (!nl)
			return (NULL);
	}
	if (nl->n == 0)
		return (free(nl->buffer), NULL); // modificar para struct
	ft_initialize_struct(nl, fd);
	if (nl->n == -1)
		return (NULL);// free struct!
	nl->total_size += nl->n;
	temp = newstring(nl);
	if (!temp)
		return (NULL);// free struct!
}
