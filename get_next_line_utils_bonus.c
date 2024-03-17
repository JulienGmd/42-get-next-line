/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:07:46 by jgrimaud          #+#    #+#             */
/*   Updated: 2024/01/04 23:47:53 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

/**
 * (Re)allocate ptr to size bytes. If size is 0, free ptr.
 * @return size or 0 if size is 0 or if malloc failed.
 */
size_t	ft_realloc(char **ptr, size_t size, size_t old_size)
{
	char	*new_ptr;
	size_t	i;

	if (!ptr)
		return (0);
	new_ptr = NULL;
	if (size > 0)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
			return (0);
		if (*ptr)
		{
			i = min(size, old_size);
			while (i--)
				new_ptr[i] = (*ptr)[i];
		}
	}
	free(*ptr);
	*ptr = new_ptr;
	return (size);
}
