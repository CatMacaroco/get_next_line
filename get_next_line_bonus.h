/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmacaroc <cmacaroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:07:16 by cmacaroc          #+#    #+#             */
/*   Updated: 2025/11/13 13:01:49 by cmacaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s, size_t n);
char	*join_and_free(char *str1, char *str2);
char	*extract_line(char **leftover);
char	*read_until_newline(int fd, char *line, char **leftover);
void	*free_and_null(char *buffer, char *line, char **leftover);
char	*handle_newline(char *line, char *buffer, char **leftover);

#endif