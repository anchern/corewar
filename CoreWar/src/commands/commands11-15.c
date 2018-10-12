#include "../../inc/vm_init.h"

unsigned int	store_index_function(t_options *options, t_player *player,
		t_sell *field)
{
	unsigned int b;
	unsigned int c;
	unsigned int result;

	result = 3;
	if (options->option_number[1] == 1)
	{
		result++;
		b = player->registry[options->reg[1] - 1];
	}
	else if (options->option_number[1] == 2)
	{
		result += 2;
		options->dir[1] = (short)options->dir[1];
		b = options->dir[1];
	}
	else if (options->option_number[1] == 3)
	{
		result += 2;
		b = bytestoui(field, player->pc->pc_index +
							 (short)(options->ind[1] % IDX_MOD));
	}
	else
		return (1);
	if (options->option_number[2] == 1)
	{
		result++;
		c = player->registry[options->reg[2] - 1];
	}
	else if (options->option_number[2] == 2)
	{
		result += 2;
		options->dir[2] = (short)options->dir[2];
		c = options->dir[2];
	}
	else
		return (1);

	uitobytes(player->registry[options->reg[0] - 1], field, player->pc->pc_index +
							(short)((short)(b + c) % IDX_MOD));
	return (result);
}

void			push_back(t_pc *start, t_pc *new_elem)
{
	if (start->next == 0)
	{
		start->next = new_elem;
		return ;
	}
	push_back(start->next, new_elem);
}

unsigned int	fork_function(t_options *options, t_player *player)
{
	t_pc *new_pc;

	new_pc = init_pc();
	nulling_pc(new_pc, true_value_pc_index(player->pc->pc_index + (short)((short)options->dir[0] % IDX_MOD)));
	new_pc->alive_label = player->pc->alive_label;
	new_pc->next = 0;
	push_back(player->pc, new_pc);
	return (3);
}

unsigned int	long_load_command(t_options *options, t_player *player, t_sell *field)
{
	unsigned int result;

	result = 1;
	if (options->option_number[0] == 2)
	{
		result += 4;
		player->registry[options->reg[1] - 1] = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		result += 2;
		player->registry[options->reg[1] - 1] = bytestoui(field,
				player->pc->pc_index + options->ind[0]);
	}
	if (player->registry[options->reg[1] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (result);
}

unsigned int	long_load_index_function(t_options *options, t_player *player,
		t_sell *field)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;

	a = 0;
	b = 0;
	result = 1;
	if (options->option_number[0] == 1)
	{
		result++;
		a = player->registry[options->reg[0] - 1];
	}
	else if (options->option_number[0] == 2)
	{
		result += 2;
		options->dir[0] = (short)options->dir[0];
		a = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		result += 2;
		a = bytestoui(field, player->pc->pc_index +
							 (short)(options->ind[0] % IDX_MOD));
	}
	if (options->option_number[1] == 1)
	{
		result++;
		b = player->registry[options->reg[1] - 1];
	}
	else if (options->option_number[0] == 2)
	{
		result += 2;
		options->dir[1] = (short)options->dir[1];
		b = options->dir[1];
	}
	player->registry[options->reg[2] - 1] = bytestoui(field,
			player->pc->pc_index + (short)((short)(a + b) % FIELD_SIZE));
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (result);
}


unsigned int	long_fork_function(t_options *options, t_player *player)
{
	t_pc *new_pc;

	new_pc = init_pc();
	nulling_pc(new_pc, true_value_pc_index(player->pc->pc_index + (short)options->dir[0]));
	new_pc->alive_label = player->pc->alive_label;
	new_pc->next = 0;
	push_back(player->pc, new_pc);
	return (3);
}