/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecosta <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:41:53 by jecosta           #+#    #+#             */
/*   Updated: 2024/12/09 17:16:46 by jecosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*ft_read_line(int fd, char *buffer, char *rest_line);
char		*ft_line_extract(char *rest_line);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*rest_line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = ft_read_line(fd, buffer, rest_line[fd]);
	free(buffer);
	if (!line)
	{
		rest_line[fd] = 0;
		return (NULL);
	}
	rest_line[fd] = ft_line_extract(line);
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
	{
		rest_line = ft_substr(line, i + 1, ft_strlen(line) - i);
	}
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
int main(void)
{
	int fd1, fd2, fd3, fd4, fd5;
	char *line1, *line2, *line3, *line4, *line5;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	fd4 = open("test4.txt", O_RDONLY);
	fd5 = open("test5.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1 || fd5 == -1)
	{
		perror("Erro ao abrir os arquivos");
		return (1);
	}

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		line4 = get_next_line(fd4);
		line5 = get_next_line(fd5);

		if (!line1 && !line2 && !line3 && !line4 && !line5)
			break;
		if (line1)
		{
			printf("test1.txt: %s", line1);
			free(line1);
		}
		if (line2)
        	{
            	printf("test2.txt: %s", line2);
            	free(line2);
		}
		if (line3)
		{
			printf("test3.txt: %s", line3);
			free(line3);
		}
		if (line4)
		{
			printf("test4.txt: %s", line4);
			free(line4);
		}
		if (line5)
		{
			printf("test5.txt: %s", line5);
			free(line5);
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
	
	return 0;
}*/
