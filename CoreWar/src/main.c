/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:41:55 by achernys          #+#    #+#             */
/*   Updated: 2018/10/03 19:36:15 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm_init.h"

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

int			main(int argc, char **argv)
{
	t_data_prog *data_prog;
	char dir_size;
	char	value;

	data_prog = (t_data_prog *)ft_memalloc(sizeof(t_data_prog));
	data_prog->game_info = init_game_info();
	data_prog->options = init_options(data_prog->options);
	data_prog->player = init_player();
	data_prog->arrays = init_arrays(data_prog->arrays);

	nulling_options(data_prog->options);
	nulling_player_and_gameinfo(data_prog->player, data_prog->game_info);



	set_players(data_prog, 1, argc, argv);
	print_field(data_prog->game_info);
	init_options_array(&data_prog->arrays);
	init_function_array(&data_prog->arrays);

	data_prog->player->pc->command =
			data_prog->game_info->field[data_prog->player->pc->pc_index].value;
	value = data_prog->player->pc->command;
	if (value  == 1 && !(value < 1 || value > 16))
		data_prog->arrays->options_array[value - 1](data_prog->options,
	data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4);
	else if (!(value < 1 || value > 16))
		data_prog->arrays->options_array[value - 1](data_prog->options,
	data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2);
	if (value  == 1 && !(value < 1 || value > 16))
		data_prog->player->pc->pc_index += alive_command(data_prog->options,
				data_prog->player, data_prog->game_info->counter);
	else if (!(value < 1 || value > 16))
	{
		data_prog->player->pc->pc_index +=
		data_prog->arrays->funtions_array[value - 2](data_prog->options,
		data_prog->player, data_prog->game_info->field);
	}

}
