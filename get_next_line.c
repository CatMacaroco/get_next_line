/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmacaroc <cmacaroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:07:44 by cmacaroc          #+#    #+#             */
/*   Updated: 2025/11/13 13:03:00 by cmacaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//static remembers where it stopped in the previous call
char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (leftover)
	{
		line = extract_line(&leftover);
		if (ft_strchr(line, '\n'))
			return (line);
	}
	line = read_until_newline(fd, line, &leftover);
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

//returns a pointer to the first occurence of char c in the string s
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

//returns a pointer to the storage space containing the copied string
char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

//used when read() return -1, aka fails
void	*free_and_null(char *buffer, char *line, char **leftover)
{
	free(buffer);
	free(line);
	if (leftover && *leftover)
	{
		free(*leftover);
		*leftover = NULL;
	}
	return (NULL);
}

//had too many lines in read_until_newline
char	*handle_newline(char *line, char *buffer, char **leftover)
{
	char	*newlineposition;

	newlineposition = ft_strchr(line, '\n');
	if (newlineposition)
	{
		*leftover = ft_strdup(newlineposition + 1);
		*(newlineposition + 1) = '\0';
		return (free(buffer), line);
	}
	return (NULL);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
