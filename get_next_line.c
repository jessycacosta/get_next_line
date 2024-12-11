/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecosta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:41:53 by jecosta           #+#    #+#             */
/*   Updated: 2024/12/11 18:48:29 by jecosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*rest_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_read_line(fd, buffer, rest_line);
	free(buffer);
	if (!line)
		return (rest_line = 0, NULL);
	rest_line = ft_line_extract(line);
	return (line);
}

char	*ft_read_line(int fd, char *buffer, char *rest_line)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(rest_line), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (rest_line == NULL)
			rest_line = ft_strdup("");
		if (!rest_line)
			return (NULL);
		temp = rest_line;
		rest_line = ft_strjoin(temp, buffer);
		free(temp);
		if (!rest_line)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest_line);
}

char	*ft_line_extract(char *line)
{
	int		i;
	char	*rest_line;

	i = 0;
	rest_line = NULL;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	if (line[i] == '\n')
		rest_line = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*rest_line == '\0')
	{
		free(rest_line);
		rest_line = NULL;
	}
	line[i + 1] = '\0';
	return (rest_line);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_size;
	size_t	i;

	src_size = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_size);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	t1;
	size_t	t2;

	i = 0;
	t1 = ft_strlen(dest);
	t2 = ft_strlen(src);
	if (size <= t1)
		return (t2 + size);
	while (src[i] != '\0' && t1 + i < size - 1)
	{
		dest[t1 + i] = src[i];
		i++;
	}
	dest[t1 + i] = '\0';
	return (t1 + t2);
}

/*#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
