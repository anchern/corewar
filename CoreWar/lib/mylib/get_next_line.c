/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 19:21:27 by achernys          #+#    #+#             */
/*   Updated: 2018/02/28 20:11:14 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_realloc(char **src, size_t size, size_t reqsize)
{
	char *str_tmp;

	if (src == 0 || reqsize == 0)
		return (0);
	if (size == 0)
	{
		ft_memdel((void **)src);
		if (!(*src = (char *)ft_memalloc(reqsize)))
			return (1);
		return (0);
	}
	if (!(str_tmp = (char *)ft_memalloc(size > reqsize ? reqsize : size)))
		return (1);
	ft_memmove((void *)str_tmp, (void *)*src, size > reqsize ? reqsize : size);
	ft_memdel((void **)src);
	if (!(*src = (char *)ft_memalloc(reqsize)))
	{
		ft_memdel((void **)&str_tmp);
		return (1);
	}
	ft_memmove((void *)*src, (void *)str_tmp, size > reqsize ? reqsize : size);
	ft_memdel((void *)&str_tmp);
	return (0);
}

static int		get_line(char **line, t_lstr *lst, int flag)
{
	size_t	i;
	size_t	size;

	i = 0;
	while (1)
	{
		if (i == lst->buf_s && flag == 0)
			return (0);
		if ((lst->buf)[i] == '\n' || i == lst->buf_s)
		{
			if (!(*line = ft_strnew(sizeof(**line) * i)))
				return (-1);
			ft_memmove(*line, lst->buf, i);
			size = lst->buf_s;
			lst->buf_s = (lst->buf)[i] == '\n' ? lst->buf_s - i - 1 :
						lst->buf_s - i;
			ft_memmove(lst->buf, &lst->buf[i + 1], lst->buf_s);
			if (ft_realloc(&lst->buf, size, lst->buf_s))
				return (-1);
			(*line)[i] = '\0';
			return (1);
		}
		i++;
	}
}

static t_lstr	*free_lst(int fd, t_lstr **str_lstr)
{
	t_lstr *tmp;

	if ((*str_lstr)->save_fd == fd)
	{
		tmp = (*str_lstr)->next;
		ft_memdel((void **)&((*str_lstr)->buf));
		ft_memdel((void **)&(*str_lstr));
		if (tmp != NULL)
			*str_lstr = tmp;
		return ((t_lstr *)-1);
	}
	if (((*str_lstr)->next)->save_fd == fd)
	{
		tmp = ((*str_lstr)->next)->next;
		ft_memdel((void **)&((*str_lstr)->next)->buf);
		ft_memdel((void **)&((*str_lstr)->next));
		(*str_lstr)->next = tmp;
		return ((t_lstr *)-1);
	}
	free_lst(fd, &((*str_lstr)->next));
	return ((t_lstr *)-1);
}

static t_lstr	*getlist(int fd, t_lstr **str_lstr)
{
	if (*str_lstr == 0)
	{
		if (!(*str_lstr = (t_lstr *)ft_memalloc(sizeof(t_lstr))))
			return (NULL);
		(*str_lstr)->save_fd = fd;
		(*str_lstr)->buf_s = 0;
		(*str_lstr)->buf = NULL;
		(*str_lstr)->next = NULL;
		return (*str_lstr);
	}
	if (fd == (*str_lstr)->save_fd)
		return (*str_lstr);
	if ((*str_lstr)->next == NULL)
	{
		if (!((*str_lstr)->next = (t_lstr *)ft_memalloc(sizeof(**str_lstr))))
			return (NULL);
		((*str_lstr)->next)->save_fd = fd;
		((*str_lstr)->next)->buf_s = 0;
		((*str_lstr)->next)->buf = NULL;
		((*str_lstr)->next)->next = NULL;
		return ((*str_lstr)->next);
	}
	return (getlist(fd, &((*str_lstr)->next)));
}

int				get_next_line(const int fd, char **line)
{
	static t_lstr	*str_lstr;
	t_lstr			*curl;
	ssize_t			read_b;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE < 1 || !(curl = getlist(fd, &str_lstr)))
		return (-1);
	if (curl->buf_s > 0 && (*buf = (char)get_line(line, curl, 0)) != 0)
		return ((int)*buf);
	while ((read_b = read(fd, buf, BUFF_SIZE)) > 0)
	{
		curl->buf_s += read_b;
		if (ft_realloc(&curl->buf, curl->buf_s - read_b, curl->buf_s))
			return ((int)free_lst(fd, &str_lstr));
		ft_memmove((void *)&curl->buf[curl->buf_s - read_b],
			(void *)buf, (size_t)read_b);
		if (read_b < BUFF_SIZE || ft_strchr(buf, '\n') != 0)
			break ;
	}
	if (read_b <= 0 && curl->buf_s <= 0)
	{
		free_lst(fd, &str_lstr);
		return (read_b < 0 ? -1 : 0);
	}
	return (get_line(line, curl, 1) < 0 ? (int)free_lst(fd, &str_lstr) : 1);
}
