/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:07:50 by jgrimaud          #+#    #+#             */
/*   Updated: 2023/12/14 12:50:44 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# define REALLOC_STEP 1024
# define OPEN_MAX 1024

typedef struct s_buf
{
	char	*str;
	size_t	len;
	size_t	max_len;
}	t_buf;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
size_t	max(size_t a, size_t b);
size_t	min(size_t a, size_t b);
void	ft_strcpy(char *dst, const char *src);
size_t	ft_realloc(char **ptr, size_t size, size_t old_size);

#endif
