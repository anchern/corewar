/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/09/26 11:49:00 by achernys         ###   ########.fr       */
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

void	nulling_options(t_options *options)
{
	int i;

	i = 0;
	while (i < 3)
	{
		options->dir[i] = 0;
		options->reg[i] = 0;
		if (i < 2)
			options->ind[i] = 0;
		options->option_number[i] = 0;
		i++;
	}
}


int main()
{



	header_t	*header;
	t_game_info	*game_info;
	t_options	*options;
	t_player	*player;
	int			fd;
	char dir_size;
	char	value;

	header = (header_t *)ft_memalloc(sizeof(header_t));
	game_info = (t_game_info *)ft_memalloc(sizeof(t_game_info));
	player = (t_player *)ft_memalloc(sizeof(t_player));
	options = (t_options *)ft_memalloc(sizeof(t_options));

	if (!(fd = read_header(game_info, header, "../files/helltrain.cor")))
	{
		close(fd);
		exit(75);
	}
	nulling_options(options);

	char (*options_array[])(t_options *options, t_sell *field, short pc_i, char dir_size) =
			{
				&d_options,
				&di_r_options,
				&r_ri_options,
				&r_r_r_options,
				&r_r_r_options,
				&rdi_rdi_r_options,
				&rdi_rdi_r_options,
				&rdi_rdi_r_options,
				&d_options,
				&rdi_rd_r_options,
				&r_rdi_rd_options,
				&d_options,
				&di_r_options,
				&rdi_rd_r_options,
				d_options
			};
	player->pc.pc_index = 0;
	player->alive_counter = 0;
	player->carry = 0;
	player->last_live = 0;
	player->player_number = (unsigned)-3;
	player->next = NULL;
	player->pc.next = NULL;
	player->pc.alive_label = 0;
	player->pc.time_todo = 0;


	game_info->counter = 0;
	game_info->cycle_delta_counter = 0;
	game_info->max_checks_counter = 0;

	player->pc.command = game_info->field[player->pc.pc_index].value;
	value = player->pc.command;
	if (value  == 1 && !(value < 1 || value > 16))
		options_array[value - 1](options, game_info->field, player->pc.pc_index + (short)1, 4);
	else if (!(value < 1 || value > 16))
		options_array[value - 1](options, game_info->field, player->pc.pc_index + (short)1, 2);

	unsigned int (*funtions_array[])(t_options *options, t_player *player, t_sell *field) =
			{
				&load_command,
				&store_command,
				&addition_command,
				&substraction_command,
				&and_function,
				&or_function,
				&xor_function,
				&jump_function,
				&load_index_function,
				&store_index_function,
				&fork_function,
				&long_load_command,
				&long_load_index_function,
				&long_fork_function
			};
	if (value  == 1 && !(value < 1 || value > 16))
		player->pc.pc_index += alive_command(options, player, game_info->counter);
	else if (!(value < 1 || value > 16))
	{
		player->pc.pc_index += funtions_array[value - 2](options, player, game_info->field);
	}
	ft_printf("\n");
	print_field(game_info);
	ft_printf("\n");

	ft_printf("%x", player->registry[1]);

}
