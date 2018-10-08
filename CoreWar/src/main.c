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

#include "../inc/vm_init.h"

void	init_time_to_do_list(unsigned short *to_do_list)
{
	to_do_list[0] = (unsigned short)10;
	to_do_list[1] = (unsigned short)5;
	to_do_list[2] = (unsigned short)5;
	to_do_list[3] = (unsigned short)10;
	to_do_list[4] = (unsigned short)10;
	to_do_list[5] = (unsigned short)6;
	to_do_list[6] = (unsigned short)6;
	to_do_list[7] = (unsigned short)6;
	to_do_list[8] = (unsigned short)20;
	to_do_list[9] = (unsigned short)25;
	to_do_list[10] = (unsigned short)25;
	to_do_list[11] = (unsigned short)800;
	to_do_list[12] = (unsigned short)10;
	to_do_list[13] = (unsigned short)50;
	to_do_list[14] = (unsigned short)1000;
}

void	print_field(t_game_info *game_info)
{
	int		i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < FIELD_SIZE)
	{
		if (game_info->field[i].value == 12)
			ft_printf("{red}%02x{eoc}", game_info->field[i].value);
		else
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

void	processing_pc(t_data_prog *data_prog)
{
	char tmp;
	unsigned char value;

	tmp = 0;
	value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
	if (data_prog->player->pc->command == 0)
	{
		if (value == 1)
		{
			tmp = data_prog->arrays->options_array[value - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2);
		}
		else if (value > 1 && value < 16)
		{
			tmp = data_prog->arrays->options_array[value - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4);
		}
		if (tmp == 1)
		{
			data_prog->player->pc->command = value;
			data_prog->player->pc->time_todo = data_prog->to_do_list[value - 1];
		}
		else
			data_prog->player->pc->pc_index++;
	}
	else if (data_prog->player->pc->time_todo == 0)
	{
		if (value == 1)
		{
			data_prog->player->pc->pc_index += alive_command(data_prog->options, data_prog->player, data_prog->game_info->counter);
		}
		else if (value > 1 && value < 16)
		{
			if (value == 9)
				data_prog->player->pc->pc_index += (int)(data_prog->arrays->functions_array[value - 2](data_prog->options, data_prog->player, data_prog->game_info->field));
			else
				data_prog->player->pc->pc_index += (data_prog->arrays->functions_array[value - 2](data_prog->options, data_prog->player, data_prog->game_info->field));
		}
	}
}



int main(int argc, char **argv)
{
	t_data_prog 	*data_prog;
	int				fd;
	char 			dir_size;
	unsigned char	value;
	int 			cycle_to_die;
	int 			cycle_todie;
	unsigned short	*to_do_list;
	t_pc			*pc_tmp;
	t_pc			*pc_tmp1;
	char 			tmp;
	int 			i;
	int 			label;


	i = 0;
	pc_tmp = (t_pc *)ft_memalloc(sizeof(t_pc));
	pc_tmp1 = (t_pc *)ft_memalloc(sizeof(t_pc));
	to_do_list = (unsigned short *)ft_memalloc(sizeof(unsigned short) * 15);
	init_time_to_do_list(to_do_list);
	data_prog = (t_data_prog *)ft_memalloc(sizeof(t_data_prog));
	init_time_to_do_list(data_prog->to_do_list);

	cycle_to_die = CYCLE_TO_DIE;
	data_prog->game_info = init_game_info();
	data_prog->options = init_options(data_prog->options);
	data_prog->player = init_player();
	data_prog->arrays = init_arrays(data_prog->arrays);

	nulling_options(data_prog->options);
	nulling_player_and_gameinfo(data_prog->player, data_prog->game_info);
	init_options_array(&data_prog->arrays);
	init_function_array(&data_prog->arrays);


	nulling_options(data_prog->options);


	nulling_options(data_prog->options);

	value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;

	set_players(data_prog, 1, argc, argv);
	print_field(data_prog->game_info);
	//TODO : написать для всех игроков
//	while (cycle_to_die > 0)
//	{
//		cycle_todie = 0;
//		while(cycle_todie < cycle_to_die)
//		{
//			//ft_printf("index %d command %x  todo %d  value %x\n",data_prog->player->pc->pc_index, data_prog->player->pc->command, data_prog->player->pc->time_todo, data_prog->game_info->field[data_prog->player->pc->pc_index].value);
//			pc_tmp1 = data_prog->player->pc;
//			while (data_prog->player->pc != NULL)
//			{
//				label = 0;
//				value = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
//
//				if (data_prog->player->pc->time_todo == 0 && data_prog->player->pc->command == 0)
//				{
//					label = 2;
//					tmp = 0;
//					if (value  == 1)
//						(tmp = data_prog->arrays->options_array[(value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4));
//					else if (value >= 1 && value < 16)
//						(tmp = data_prog->arrays->options_array[(value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2));
//					if (tmp == 1)
//					{
//						data_prog->player->pc->command = value;
//						data_prog->player->pc->time_todo = to_do_list[value - 1];
//					}
//					else
//						data_prog->player->pc->pc_index++;
//				}
//				if (data_prog->player->pc->time_todo == 0 && data_prog->player->pc->command != 0)
//				{
//					label += 1;
//					if (value  == 1 && !(value < 1 || value > 16))
//						data_prog->player->pc->pc_index += alive_command(data_prog->options,
//																		 data_prog->player, data_prog->game_info->counter);
//					else if (!(value < 1 || value > 16))
//					{
//						if (value == 9)
//							data_prog->player->pc->pc_index +=
//									(int)(data_prog->arrays->functions_array[value - 2](data_prog->options,
//																				  data_prog->player, data_prog->game_info->field));
//						else
//							data_prog->player->pc->pc_index +=
//									data_prog->arrays->functions_array[value - 2](data_prog->options,
//																				  data_prog->player, data_prog->game_info->field);
//					}
//					data_prog->player->pc->command = 0;
//					nulling_options(data_prog->options);
//				}
//				if (data_prog->player->pc->time_todo == 0 && data_prog->player->pc->command == 0 && label == 1)
//				{
//					tmp = 0;
//					if (data_prog->game_info->field[data_prog->player->pc->pc_index].value  == 1 && !(data_prog->game_info->field[data_prog->player->pc->pc_index].value < 1 || value > 16))
//						(tmp = data_prog->arrays->options_array[(data_prog->game_info->field[data_prog->player->pc->pc_index].value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 4));
//					else if (!(data_prog->game_info->field[data_prog->player->pc->pc_index].value < 1 || data_prog->game_info->field[data_prog->player->pc->pc_index].value > 16))
//					{
//						(tmp = data_prog->arrays->options_array[(data_prog->game_info->field[data_prog->player->pc->pc_index].value) - 1](data_prog->options, data_prog->game_info->field, data_prog->player->pc->pc_index + (short)1, 2));
//					}
//					if (tmp == 1)
//					{
//						data_prog->player->pc->command = data_prog->game_info->field[data_prog->player->pc->pc_index].value;
//						data_prog->player->pc->time_todo = to_do_list[value - 1];
//					}
//					else
//					{
//						data_prog->player->pc->pc_index++;
//					}
//				}
//				data_prog->player->pc = data_prog->player->pc->next;
//			}
//			data_prog->player->pc = pc_tmp1;
//			cycle_todie++;
//			data_prog->game_info->counter++;
//			if (data_prog->player->pc->time_todo != 0)
//				data_prog->player->pc->time_todo--;
//			data_prog->player->pc->pc_index = true_value_pc_index(data_prog->player->pc->pc_index);
//		}
//
//		data_prog->game_info->max_checks_counter++;
//		if (data_prog->player->alive_counter != -1)
//		{
//			if (data_prog->game_info->counter - data_prog->player->last_live >
//				CYCLE_TO_DIE)
//				data_prog->player->alive_counter = -1;
//			if (data_prog->player->alive_counter > 21)
//			{
//				data_prog->game_info->max_checks_counter = 0;
//				cycle_to_die = cycle_to_die - CYCLE_DELTA;
//			}
//		}
//		if (data_prog->game_info->max_checks_counter == 9)
//		{
//			cycle_to_die = cycle_to_die - CYCLE_DELTA;
//			data_prog->game_info->max_checks_counter = 0;
//		}
//		pc_tmp1 = data_prog->player->pc;
//
//		while (pc_tmp1 != 0)
//		{
//
//			if (pc_tmp1->alive_label == 0)
//			{
//				pc_tmp = pc_tmp1;
//				pc_tmp1 = pc_tmp1->next;
//				free(pc_tmp);
//				pc_tmp = 0;
//			}
//			else if (pc_tmp1->next->alive_label == 0)
//			{
//				pc_tmp = pc_tmp1->next;
//				pc_tmp1->next = pc_tmp1->next->next;
//				free(pc_tmp);
//				pc_tmp = 0;
//			}
//			if (pc_tmp1 != 0)
//				pc_tmp1 = pc_tmp1->next;
//		}
//		data_prog->player->pc = pc_tmp1;
//	}




















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
