/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:22:57 by achernys          #+#    #+#             */
/*   Updated: 2018/02/28 20:11:56 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1

# include <fcntl.h>
# include "./libft/libft.h"

typedef struct	s_lstr
{
	int				save_fd;
	size_t			buf_s;
	char			*buf;
	struct s_lstr	*next;
}				t_lstr;

int				get_next_line(const int fd, char **line);
int				ft_realloc(char **src, size_t size, size_t reqsize);
#endif
