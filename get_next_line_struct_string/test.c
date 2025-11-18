/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:23:33 by msobral-          #+#    #+#             */
/*   Updated: 2025/11/17 17:53:28 by msobral-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	
	if (argc < 2)
	{
		fd = 1;
		line = get_next_line(fd);
		if (!line)
			return (printf("No input file or valid standard input\n"));
		printf("File Descriptor = %d\n", fd);
		i = 1;
		while (line >= 1)
		{
			printf("line %d = %s", i++, line);
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		line = NULL;
		close(fd);
	}
	else
	{
		j = 1;
		while (argv[j])
		{
			fd = open(argv[j], O_RDONLY);
			if (fd == -1)
			{
				printf("Failed to open file %d\n", j++);
				break ;
			}
			printf("File Descriptor = %d\n", fd);
			line = get_next_line(fd);
			i = 1;
			while (line)
			{
				printf("line %d = %s", i++, line);
				free(line);
				line = get_next_line(fd);
			}
			free(line);
			line = NULL;
			close(fd);
			j++;
		}
	}
	return (0);
}

	/*	printf("line 1 = %s", line);
		line = get_next_line(fd);
		printf("line 2 = %s", line);
		line = get_next_line(fd);
		printf("line 3 = %s", line);
		line = get_next_line(fd);
		printf("line 4 = %s", line);
		line = get_next_line(fd);
		printf("line 5 = %s", line);
		line = get_next_line(fd);
		printf("line 6 = %s", line);
		line = get_next_line(fd);
		printf("line 7 = %s", line);
		line = get_next_line(fd);
		printf("line 8 = %s", line);
		line = get_next_line(fd);
		printf("line 9 = %s", line); */