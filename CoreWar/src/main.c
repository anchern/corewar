/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/09/22 02:41:55 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	save_in_var(unsigned int *var, unsigned char *arr)
{
	*var = (*var | arr[0]) << 8;
	*var = (*var | arr[1]) << 8;
	*var = (*var | arr[2]) << 8;
	*var = *var | arr[3];
}

void	copy_field(t_game_info *game_info, unsigned char *field, int field_size)
{
	int		i;

	i = 0;
	while (i < field_size)
	{
		game_info->field[i].value = field[i];
		i++;
	}
}

void	print_field(t_game_info *game_info)
{
	int		i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < FIELD_SIZE)
	{
		ft_printf("%02x", game_info->field[i].value);
		if (!((i + 1) % 64))
		{
			ft_printf("\n");
			if (i != FIELD_SIZE - 1)
				ft_printf("%#06x : ", i + 1);
		}
		else
			ft_printf(" ");
		i++;
	}
}


int		read_header(t_game_info *game_info, header_t *header, char *filename)
{
	unsigned char	buf[COMMENT_LENGTH + 1];
	int				fd;
	ssize_t 		rd;

	fd = open(filename, O_RDONLY);
	header->magic = 0;
	if (fd < 0)
		return (0);
	if (read(fd,buf, 4) < 4)
		return (0);
	save_in_var(&header->magic, buf);
	if (read(fd, buf, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
		return (0);
	ft_strcpy(header->prog_name, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (0);
	if (read(fd, buf, 4) < 4)
		return (0);
	save_in_var(&header->prog_size, buf);
	if (read(fd, buf, COMMENT_LENGTH) < COMMENT_LENGTH)
		return (0);
	ft_strcpy(header->comment, (char *)buf);
	if (read(fd, buf, 4) < 4)
		return (0);
	if ((rd = read(fd, buf, header->prog_size)) < header->prog_size || rd > 682)
		return (0);
	copy_field(game_info, buf, header->prog_size);
	print_field(game_info);
	return (fd);
}

int		main (int argc, char **argv)
{
	header_t	*header;
	t_game_info	*game_info;
	t_options	*options;
	t_player	*player;
	int			fd;

	header = (header_t *)ft_memalloc(sizeof(header_t));
	game_info = (t_game_info *)ft_memalloc(sizeof(t_game_info));
	if (!(fd = read_header(game_info, header, "../files/helltrain.cor")))
	{
		close(fd);
		exit(75);
	}
	return (0);
}