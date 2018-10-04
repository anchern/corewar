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
	if ((rd = read(fd, buf, header->prog_size)) < header->prog_size || rd > CHAMP_MAX_SIZE)
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

void	nulling_player_and_gameinfo(t_player *player, t_game_info *game_info)
{
	player->pc->pc_index = 0;
	player->alive_counter = 0;
	player->carry = 0;
	player->last_live = 0;
	player->player_number = 0;
	player->next = NULL;
	player->pc->next = NULL;
	player->pc->alive_label = 0;
	player->pc->time_todo = 0;
	game_info->counter = 0;
	game_info->cycle_delta_counter = 0;
	game_info->max_checks_counter = 0;
	game_info->cycle_delta_counter = 0;
}

t_player	*init_player(t_player *player)
{
	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))) ||
		!(player->pc = (t_pc *)ft_memalloc(sizeof(t_pc))))
		exit(1337);
	return (player);
}

t_options	*init_options(t_options *options)
{
	if (!(options = (t_options *)ft_memalloc(sizeof(t_options))))
		exit(1337);
	return (options);
}

t_game_info	*init_game_info(t_game_info *game_info)
{
	if (!(	game_info = (t_game_info *)ft_memalloc(sizeof(t_game_info))))
		exit(1337);
	return (game_info);
}

header_t	*init_header(header_t *header)
{
	if (!(	header = (header_t *)ft_memalloc(sizeof(header_t))))
		exit(1337);
	return (header);
}

t_arrays	*init_arrays(t_arrays *arrays)
{
	if (!(arrays = (t_arrays *)malloc(sizeof(t_arrays))))
		exit(1337);
	return (arrays);
}

void	*init_options_array(t_arrays **arrays)
{
	(*arrays)->options_array[0] = &d_options;
	(*arrays)->options_array[1] = &di_r_options;
	(*arrays)->options_array[2] = &r_ri_options;
	(*arrays)->options_array[3] = &r_r_r_options;
	(*arrays)->options_array[4] = &r_r_r_options;
	(*arrays)->options_array[5] = &rdi_rdi_r_options;
	(*arrays)->options_array[6] = &rdi_rdi_r_options;
	(*arrays)->options_array[7] = &rdi_rdi_r_options;
	(*arrays)->options_array[8] = &d_options;
	(*arrays)->options_array[9] = &rdi_rd_r_options;
	(*arrays)->options_array[10] = &r_rdi_rd_options;
	(*arrays)->options_array[11] = &d_options;
	(*arrays)->options_array[12] = &di_r_options;
	(*arrays)->options_array[13] = &rdi_rd_r_options;
	(*arrays)->options_array[14] = &d_options;
}

void	*init_function_array(t_arrays **arrays)
{
	(*arrays)->functions_array[0] = &load_command;
	(*arrays)->functions_array[1] = &store_command;
	(*arrays)->functions_array[2] = &addition_command;
	(*arrays)->functions_array[3] = &substraction_command;
	(*arrays)->functions_array[4] = &and_function;
	(*arrays)->functions_array[5] = &or_function;
	(*arrays)->functions_array[6] = &xor_function;
	(*arrays)->functions_array[7] = &jump_function;
	(*arrays)->functions_array[8] = &load_index_function;
	(*arrays)->functions_array[9] = &store_index_function;
	(*arrays)->functions_array[10] = &fork_function;
	(*arrays)->functions_array[11] = &long_load_command;
	(*arrays)->functions_array[12] = &long_load_index_function;
	(*arrays)->functions_array[13] = &long_fork_function;
}

void	nulling_header(header_t *header)
{
	header->magic = 0;
	header->prog_size = 0;
}

void	init_time_to_do_list(unsigned short (*to_do_list))
{
	(to_do_list[0]) = (short)10;
	(to_do_list[1]) = (short)5;
	(to_do_list[2]) = (short)5;
	(to_do_list[3]) = (short)10;
	(to_do_list[4]) = (short)10;
	(to_do_list[5]) = (short)6;
	(to_do_list[6]) = (short)6;
	(to_do_list[7]) = (short)6;
	(to_do_list[8]) = (short)20;
	(to_do_list[9]) = (short)25;
	(to_do_list[10]) = (short)25;
	(to_do_list[11]) = (short)800;
	(to_do_list[12]) = (short)10;
	(to_do_list[13]) = (short)50;
	(to_do_list[14]) = (short)1000;
}


int main()
{
	t_data_prog *data_prog;
	int			fd;
	char dir_size;
	unsigned char	value;
	int 	cycle_to_die;
	int 	cycle_todie;
	unsigned short	*to_do_list;
	t_pc	*pc_tmp;
	t_pc	*pc_tmp1;
	char tmp;
	int i;

	i = 0;
	to_do_list = (unsigned short *)ft_memalloc(sizeof(unsigned short));
	pc_tmp = (t_pc *)ft_memalloc(sizeof(t_pc));
	pc_tmp1 = (t_pc *)ft_memalloc(sizeof(t_pc));
	init_time_to_do_list(to_do_list);
	data_prog = (t_data_prog *)ft_memalloc(sizeof(t_data_prog));

	cycle_to_die = CYCLE_TO_DIE;
	data_prog->game_info = init_game_info(data_prog->game_info);
	data_prog->options = init_options(data_prog->options);
	data_prog->player = init_player(data_prog->player);
	data_prog->header = init_header(data_prog->header);
	data_prog->arrays = init_arrays(data_prog->arrays);

	nulling_options(data_prog->options);
	nulling_player_and_gameinfo(data_prog->player, data_prog->game_info);
	nulling_header(data_prog->header);

	if (!(fd = read_header(data_prog->game_info, data_prog->header, "../files/helltrain.cor")))
	{
		close(fd);
		exit(75);
	}

	init_options_array(&data_prog->arrays);
	init_function_array(&data_prog->arrays);

	data_prog->player->player_number = (unsigned)-4;
	while (i < 15)
	{
		data_prog->player->registry[0] = (unsigned)-1;
		i++;
	}

	data_prog->player->pc = (t_pc *)ft_memalloc(sizeof(t_pc));
	data_prog->player->pc->pc_index = (short)0;
	nulling_options(data_prog->options);


	nulling_options(data_prog->options);

	value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
	//TODO : написать для всех игроков
	while (cycle_to_die > 0)
	{
		cycle_todie = 0;

		while(cycle_todie < cycle_to_die)
		{
//			ft_printf("index %d command %d  todo %d  value %x\n",data_prog->player->pc->pc_index, data_prog->player->pc->command, data_prog->player->pc->time_todo, data_prog->game_info->field[data_prog->player->pc->pc_index].value);
			pc_tmp1 = data_prog->player->pc;
			while (data_prog->player->pc != NULL)
			{
				value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;

				if (data_prog->player->pc->time_todo == 0 && data_prog->player->pc->command == 0)
				{
					if (value  == 1 && !(value < 1 || value > 16))
						(tmp = data_prog->arrays->options_array[(value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4)); // TODO : посмотреть что возвращает . Если 1 то все ок если 0 то  сместить каретку на некст индекс
					else if (!(value < 1 || value > 16))
						(tmp = data_prog->arrays->options_array[(value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2));

					if (tmp == 1)
					{
						data_prog->player->pc->command = value;
						data_prog->player->pc->time_todo = to_do_list[value - 1];
					}
					if (value > 16 || value == 0)
						data_prog->player->pc->pc_index++;
				}
				if (data_prog->player->pc->time_todo == 0 && data_prog->player->pc->command != 0)
				{
					if (value  == 1 && !(value < 1 || value > 16))
						data_prog->player->pc->pc_index += alive_command(data_prog->options,
																		 data_prog->player, data_prog->game_info->counter);
					else if (!(value < 1 || value > 16))
					{
						data_prog->player->pc->pc_index +=
								data_prog->arrays->functions_array[value - 2](data_prog->options,
																			  data_prog->player, data_prog->game_info->field);
					}
					data_prog->player->pc->command = 0;
					data_prog->player->pc->time_todo = 0;
					nulling_options(data_prog->options);
				}
				if (data_prog->player->pc->time_todo == 0 && data_prog->player->pc->command == 0)
				{
					if (value  == 1 && !(value < 1 || value > 16))
						(tmp = data_prog->arrays->options_array[(value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4)); // TODO : посмотреть что возвращает . Если 1 то все ок если 0 то  сместить каретку на некст индекс
					else if (!(value < 1 || value > 16))
						(tmp = data_prog->arrays->options_array[(value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2));

					if (tmp == 1)
					{
						data_prog->player->pc->command = value;
						data_prog->player->pc->time_todo = to_do_list[value - 1];
					}
					if (value > 16 || value == 0)
						data_prog->player->pc->pc_index++;
				}

				data_prog->player->pc = data_prog->player->pc->next;
			}
			data_prog->player->pc = pc_tmp1;
			cycle_todie++;
			data_prog->game_info->counter++;
			data_prog->player->pc->time_todo--;
		}

		data_prog->game_info->max_checks_counter++;
		if (data_prog->player->alive_counter != -1)
		{
			if (data_prog->game_info->counter - data_prog->player->last_live >
				CYCLE_TO_DIE)
				data_prog->player->alive_counter = -1;
			if (data_prog->player->alive_counter > 21)
			{
				data_prog->game_info->max_checks_counter = 0;
				cycle_to_die = cycle_to_die - CYCLE_DELTA;
			}
		}
		if (data_prog->game_info->max_checks_counter == 9)
			cycle_to_die = cycle_to_die - CYCLE_DELTA;
		pc_tmp1 = data_prog->player->pc;

		while (data_prog->player->pc->next != NULL)
		{
			if (data_prog->player->pc->alive_label == 0)
			{
				pc_tmp = data_prog->player->pc;
				data_prog->player->pc = data_prog->player->pc->next;
				free(pc_tmp);
			}
			if (data_prog->player->pc->next->alive_label == 0)
			{
				pc_tmp = data_prog->player->pc->next;
				data_prog->player->pc->next = data_prog->player->pc->next->next;
				free(pc_tmp);
			}
			data_prog->player->pc = data_prog->player->pc->next;
		}
		data_prog->player->pc = pc_tmp1;
	}
















//	data_prog->player->pc->command =
//			data_prog->game_info->field[data_prog->player->pc->pc_index].value;
//	value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
//	if (value  == 1 && !(value < 1 || value > 16))
//		data_prog->arrays->options_array[value - 1](data_prog->options,
//	data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4);
//	else if (!(value < 1 || value > 16))
//		data_prog->arrays->options_array[value - 1](data_prog->options,
//	data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2);
//	if (value  == 1 && !(value < 1 || value > 16))
//		data_prog->player->pc->pc_index += alive_command(data_prog->options,
//				data_prog->player, data_prog->game_info->counter);
//	else if (!(value < 1 || value > 16))
//	{
//		data_prog->player->pc->pc_index +=
//		data_prog->arrays->functions_array[value - 2](data_prog->options,
//		data_prog->player, data_prog->game_info->field);
//	}
	ft_printf("\n");
	print_field(data_prog->game_info);
	ft_printf("\n");

//	ft_printf("%x", data_prog->player->pc->pc_index);

}
