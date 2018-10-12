#include "../../inc/vm.h"

unsigned int	alive_command(t_options *options, t_data_prog *data_prog, int counter)
{
	t_player *player_tmp;

	player_tmp = data_prog->first_player;
	data_prog->player->pc->alive_label = 1;
	while (player_tmp != NULL)
	{
		if (player_tmp->player_number == options->dir[0])
		{
			player_tmp->last_live = counter;
			player_tmp->alive_counter++;
		}
		player_tmp = player_tmp->next;
	}
	return (5);
}

unsigned int	load_command(t_options *options, t_player *player, t_sell *field)
{
	unsigned int	result;

	result = 1;
	if (options->option_number[0] == 2)
	{
		result = 7;
		player->registry[options->reg[1] - 1] = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		result = 5;
		options->ind[0] = (short)(options->ind[0] % IDX_MOD);
		player->registry[options->reg[1] - 1] = bytestoui(field,
				player->pc->pc_index + options->ind[0]);
	}
	if (player->registry[options->reg[1] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (result);
}



unsigned int	store_command(t_options *options, t_player *player, t_sell *field)
{
	unsigned int	result;

	result = 1;
	if (options->option_number[1] == 3)
	{
		uitobytes(player->registry[options->reg[0] - 1], field,
			player->pc->pc_index + (short)(options->ind[1] % IDX_MOD));
		result = 5;
	}
	else if (options->option_number[1] == 1)
	{
		player->registry[options->reg[0] - 1] =
				player->registry[options->reg[1] - 1];
		result = 4;
	}
	return (result);
}

unsigned int	 addition_command(t_options *options, t_player *player)
{
	player->registry[options->reg[2]] = player->registry[options->reg[0]]
			+ player->registry[options->reg[1]];
	if (player->registry[options->reg[2]] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (5);
}

unsigned int	substraction_command(t_options *options, t_player *player)
{
	player->registry[options->reg[2]] = player->registry[options->reg[0]]
										- player->registry[options->reg[1]];
	if (player->registry[options->reg[2]] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (5);
}