/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:14:16 by jgrimaud          #+#    #+#             */
/*   Updated: 2023/12/14 07:34:48 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_reset(char **buf, char *saved)
{
	ft_free(buf);
	saved[0] = '\0';
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_strcpy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

/**
 * Duplicates len characters starting at str.
*/
char	*ft_strdupn(char *str, size_t len)
{
	char	*dup;
	size_t	i;

	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * Try to extract a line (ending with '\n') from buf (or saved if buf is NULL),
 * if found, a duplicate of the line is returned and the remaining characters
 * (or '\0') are placed in saved.
*/
char	*ft_tryextractline(t_buf *buf, char *saved, ssize_t num_read)
{
	char	*line;
	size_t	i;
	char	*str;

	i = (buf->str != NULL) * (buf->len - num_read);
	str = buf->str;
	if (!str)
		str = saved;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n' || (num_read == 0 && i != 0))
	{
		if (str[i] == '\n')
			i++;
		line = ft_strdupn(str, i);
		if (!line)
			return ((char *)ERR_PTR);
		ft_strcpy(saved, str + i);
		return (line);
	}
	return (NULL);
}

void	ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
}

/**
 * @return true if succeeded.
*/
char	*ft_realloc(char **ptr, size_t size, size_t old_size)
{
	char	*new_ptr;

	if (!ptr)
		return (NULL);
	new_ptr = NULL;
	if (size > 0)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
			return (NULL);
		if (size > old_size)
			size = old_size;
		if (*ptr)
			ft_memmove(new_ptr, *ptr, size);
	}
	ft_free(ptr);
	*ptr = new_ptr;
	return (*ptr);
}

/**
 * Read fd into buf (which will be reallocated if needed).
 * @return read return value or -2 if malloc error.
*/
ssize_t	ft_read(int fd, t_buf *buf, char *saved)
{
	ssize_t	num_read;
	size_t	realloc_step;

	if (!buf->str)
	{
		buf->str = ft_strdupn(saved, ft_strlen(saved));
		if (!buf->str)
			return (-2);
		buf->len = ft_strlen(saved);
		buf->max_len = ft_strlen(saved);
	}
	if (buf->len + BUFFER_SIZE > buf->max_len)
	{
		realloc_step = (REALLOC_STEP >= BUFFER_SIZE) * REALLOC_STEP
			+ (REALLOC_STEP < BUFFER_SIZE) * BUFFER_SIZE;
		if (!ft_realloc(&buf->str, buf->len + realloc_step + 1, buf->len + 1))
			return (ft_free(&buf->str), -2); // TODO passer le free ds get_net_line?
		buf->max_len = buf->len + realloc_step;
	}
	num_read = read(fd, buf->str + buf->len, BUFFER_SIZE);
	if (num_read <= 0)
		return (num_read);
	buf->len += num_read;
	(buf->str)[buf->len] = '\0';
	return (num_read);
}

char	*get_next_line(int fd)
{
	static char	saved[1024][BUFFER_SIZE]; // TODO utiliser FOPEN_MAX ? // TODO init ?
	t_buf		buf;
	ssize_t		num_read;
	char		*line;

	if (read(fd, NULL, 0) < 0)
		return (saved[fd][0] = '\0', NULL);
	buf.str = NULL;
	buf.len = 0;
	buf.max_len = 0;
	num_read = -3;
	while (1)
	{
		line = ft_tryextractline(&buf, saved[fd], num_read);
		if (line == (char *)ERR_PTR)
			return (ft_free(&buf.str), NULL);
		if (line)
			return (ft_free(&buf.str), line);
		if (num_read == 0)
			return (ft_free(&buf.str), NULL);
		num_read = ft_read(fd, &buf, saved[fd]);
		if (num_read == -1 || num_read == -2)
			return (ft_reset(&buf.str, saved[fd]), NULL);
	}
}
