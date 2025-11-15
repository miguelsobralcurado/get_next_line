#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	
	if (argc < 2)
		return (printf(" No input file\n"));
	j = 1;
	while (argv[j])
	{
		fd = open(argv[j], O_RDONLY);
		if (fd == -1)
		{
			printf(" Failed to open file %d\n", j++);
			break ;
		}
		printf(" File Descriptor = %d\n", fd);
		line = get_next_line(fd);
		i = 1;
		while (line)
		{
			printf(" line %d = %s", i++, line);
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		line = NULL;
		close(fd);
		j++;
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