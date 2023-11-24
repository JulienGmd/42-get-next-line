/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrimaud <jgrimaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:07:50 by jgrimaud          #+#    #+#             */
/*   Updated: 2023/11/23 02:58:54 by jgrimaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h> // contains FOPEN_MAX
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# define ERR_PTR -1
# define REALLOC_STEP 1024

typedef struct s_buf
{
	char	*str;
	size_t	len;
	size_t	max_len;
}	t_buf;

char	*get_next_line(int fd);

#endif
