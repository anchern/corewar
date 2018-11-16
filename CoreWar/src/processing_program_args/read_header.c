/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:03:39 by dlewando          #+#    #+#             */
/*   Updated: 2018/11/16 14:03:39 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm_init.h"

char	read_mag_and_name(int fd, t_header *header)
{
	unsigned char	buf[COMMENT_LENGTH + 1];

	header->magic = 0;
	if (read(fd, buf, 4) < 4)
		return (1);
	save_in_var(&header->magic, buf);
	if (header->magic != COREWAR_EXEC_MAGIC)
		return (1);
	if (read(fd, buf, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (1);
	ft_strcpy(header->prog_name, (char *)buf);
	return (0);
}

char	read_bot_size_and_comment(int fd, t_header *header)
{
	unsigned char	buf[COMMENT_LENGTH + 1];

	if (read(fd, buf, 4) < 4)
		return (1);
	save_in_var(&header->prog_size, buf);
	if (read(fd, buf, COMMENT_LENGTH) < COMMENT_LENGTH)
		return (1);
	ft_strcpy(header->comment, (char *)buf);
	return (0);
}

int		read_header(t_game_info *game_info, t_header *header, char *filename,
					short start_position)
{
	unsigned char	buf[COMMENT_LENGTH + 1];
	int				fd;
	ssize_t			rd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		file_error(filename);
	if (fd < 0)
		return (fd);
	if (read_mag_and_name(fd, header))
		return (fd);
	if (read(fd, buf, 4) < 4)
		return (fd);
	if (read_bot_size_and_comment(fd, header))
		return (fd);
	if (read(fd, buf, 4) < 4)
		return (fd);
	if ((rd = read(fd, buf, CHAMP_MAX_SIZE + 1)) != header->prog_size ||
		rd > CHAMP_MAX_SIZE)
		return (fd);
	copy_field(game_info, buf, header->prog_size, start_position);
	close(fd);
	return (0);
}
