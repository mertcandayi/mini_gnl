#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	read_byte = 0;
	static int	pos = 0;
	char		*line;
	int			line_len;
	char		*tmp;
	char		c;

	line = NULL;
	line_len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		if (pos >= read_byte)
		{
			read_byte = read(fd, buffer, BUFFER_SIZE);
			if (read_byte <= 0)
			{
				if (line_len == 0)
				{
					free(line);
					return (NULL);
				}
				return (line);
			}
			buffer[read_byte] = '\0';
			pos = 0;
		}
		c = buffer[pos++];
		tmp = malloc(line_len + 2);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		for (int i = 0; i < line_len; i++)
			tmp[i] = line[i];
		tmp[line_len++] = c;
		tmp[line_len] = '\0';
		free(line);
		line = tmp;
		if (c == '\n')
			return (line);
	}
}
