/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmacaroc <cmacaroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:08:00 by cmacaroc          #+#    #+#             */
/*   Updated: 2025/11/13 12:14:00 by cmacaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//makes a new copy of a string but only takes a certain number of letters from 
//it—you have a long sentence and you only want to copy the first few words
char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

//calculates the length of a string, excluding the '\0' byte 
//handles NULL pointers
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*join_and_free(char *str1, char *str2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str1 && !str2)
		return (NULL);
	if (!str1)
		return (ft_strdup(str2));
	if (!str2)
		return (str1);
	joined = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!joined)
		return (free(str1), NULL);
	while (str1[i] != '\0')
	{
		joined[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
		joined[i++] = str2[j++];
	joined[i] = '\0';
	free(str1);
	return (joined);
}

char	*extract_line(char **leftover)
{
	char	*line;
	char	*newleftover;
	char	*newlineposition;
	size_t	len;

	if (!leftover || !*leftover)
		return (NULL);
	newlineposition = ft_strchr(*leftover, '\n');
	if (newlineposition)
	{
		len = newlineposition - *leftover + 1;
		line = ft_strndup(*leftover, len);
		newleftover = ft_strdup(newlineposition + 1);
		free(*leftover);
		*leftover = newleftover;
		return (line);
	}
	line = ft_strdup(*leftover);
	free(*leftover);
	*leftover = NULL;
	return (line);
}

char	*read_until_newline(int fd, char *line, char **leftover)
{
	char	*buffer;
	char	*newline;
	ssize_t	bytesread;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(line), NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
		return (free_and_null(buffer, line, leftover));
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		line = join_and_free(line, buffer);
		newline = handle_newline(line, buffer, leftover);
		if (newline)
			return (newline);
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (free_and_null(buffer, line, leftover));
	}
	return (free(buffer), line);
}
