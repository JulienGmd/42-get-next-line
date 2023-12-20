/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:14:16 by jgrimaud          #+#    #+#             */
/*   Updated: 2023/12/20 21:06:37 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Initialize buf with saved.
 * @return true if success, false if BUFFER_SIZE <= 0 or fd is invalid.
*/
static bool	init(int fd, char *saved, t_buf *buf)
{
	if (BUFFER_SIZE <= 0)
		return (false);
	if (read(fd, NULL, 0) < 0)
	{
		if (fd >= 0 && fd < OPEN_MAX)
			saved[0] = '\0';
		return (false);
	}
	buf->str = NULL;
	buf->max_len = ft_realloc(&buf->str, max(BUFFER_SIZE, REALLOC_STEP) + 1, 0);
	if (!buf->str)
		return (false);
	buf->len = ft_strlen(saved);
	ft_strcpy(buf->str, saved);
	return (true);
}

/**
 * Try to extract a line from buf and save the rest in saved.
 * @param num_read The number of bytes read by ft_read, or -3 if ft_read has
 * not been called yet.
 * @return true if a line has been extracted, false otherwise.
*/
static bool	ft_tryextractline(t_buf *buf, char *saved, ssize_t num_read)
{
	size_t	i;

	if (num_read == 0 && buf->str[0])
		return (saved[0] = '\0', true);
	i = (num_read != -3) * (buf->len - num_read);
	while (buf->str[i] && buf->str[i] != '\n')
		i++;
	if (buf->str[i] == '\n')
	{
		ft_strcpy(saved, buf->str + i + 1);
		buf->str[i + 1] = '\0';
		buf->len = i + 1;
		return (true);
	}
	return (false);
}

/**
 * Read BUFFER_SIZE bytes from fd and append them to buf.
 * @return The number of bytes read, or -1 if an error occurred, or -2 if
 * ft_realloc failed.
*/
static ssize_t	ft_read(int fd, t_buf *buf)
{
	ssize_t	num_read;

	if (buf->len + BUFFER_SIZE + 1 > buf->max_len)
	{
		if (!ft_realloc(&buf->str,
				buf->len + max(BUFFER_SIZE, REALLOC_STEP) + 1, buf->len + 1))
			return (-2);
		buf->max_len = buf->len + max(BUFFER_SIZE, REALLOC_STEP);
	}
	num_read = read(fd, buf->str + buf->len, BUFFER_SIZE);
	if (num_read <= 0)
		return (num_read);
	buf->len += num_read;
	buf->str[buf->len] = '\0';
	return (num_read);
}

/**
 * Read from fd until a line is found, then return it.
 * @return A line, or NULL if an error occurred or all lines have been read.
*/
char	*get_next_line(int fd)
{
	static char	saved[OPEN_MAX][BUFFER_SIZE];
	t_buf		buf;
	ssize_t		num_read;

	if (!init(fd, saved[fd], &buf))
		return (NULL);
	num_read = -3;
	while (42)
	{
		if (ft_tryextractline(&buf, saved[fd], num_read))
			return (ft_realloc(&buf.str, buf.len + 1, buf.len + 1), buf.str);
		if (num_read == 0)
			return (free(buf.str), NULL);
		num_read = ft_read(fd, &buf);
		if (num_read < 0)
			return (free(buf.str), NULL);
	}
}
