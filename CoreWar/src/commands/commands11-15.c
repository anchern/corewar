#include "../../inc/vm.h"

void	store_index_function(t_options *options, t_sell *field, t_player *player)
{
	unsigned int b;
	unsigned int c;

	c = 0;
	b = 0;
	if (options->option_number[1] == 1)
		b = player->registry[options->reg[1] - 1];
	else if (options->option_number[1] == 2)
		b = options->dir[1];
	else if (options->option_number[1] == 3)
	{
		b = bytestoui(field, player->pc.pc_index +
							 (short)(options->ind[1] % IDX_MOD));
	}
	if (options->option_number[2] == 1)
		c = player->registry[options->reg[2] - 1];
	else if (options->option_number[2] == 2)
		c = options->dir[2];
	uitobytes((unsigned)options->reg[0], field, player->pc.pc_index +
	(short)((b + c) % IDX_MOD));
}

void	fork_function(t_options *options, t_player *player)
{
	t_pc *new_pc;

	new_pc = (t_pc *)ft_memalloc(sizeof(t_pc));
	new_pc->alive_label = player->pc.alive_label;
	new_pc->time_todo = 0;
	new_pc->command = 0;
	new_pc->pc_index = player->pc.pc_index + (short)(options->dir[0] % IDX_MOD);
	new_pc->next = &(player->pc);
	player->pc = *new_pc;
}

void	long_load_command(t_options *options, t_sell *field, t_player *player)
{
	if (options->option_number[0] == 2)
	{
		player->registry[options->reg[1] - 1] = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		player->registry[options->reg[1] - 1] = bytestoui(field,
				player->pc.pc_index + options->ind[0]);
	}
	if (player->registry[options->reg[1] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
}

void	long_load_index_function(t_options *options, t_sell *field,
		t_player *player)
{
	unsigned int a;
	unsigned int b;

	a = 0;
	b = 0;
	if (options->option_number[0] == 1)
		a = player->registry[options->reg[0] - 1];
	else if (options->option_number[0] == 2)
		a = options->dir[0];
	else if (options->option_number[0] == 3)
	{
		a = bytestoui(field, player->pc.pc_index +
							 (short)(options->ind[0] % IDX_MOD));
	}
	if (options->option_number[1] == 1)
		b = player->registry[options->reg[1] - 1];
	else if (options->option_number[0] == 2)
		b = options->dir[1];
	player->registry[options->reg[2] - 1] = bytestoui(field,
			player->pc.pc_index + (short)((a + b) % FIELD_SIZE));
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
}


void	long_fork_function(t_options *options, t_player *player)
{
	t_pc *new_pc;

	new_pc = (t_pc *)ft_memalloc(sizeof(t_pc));
	new_pc->alive_label = player->pc.alive_label;
	new_pc->time_todo = 0;
	new_pc->command = 0;
	new_pc->pc_index = player->pc.pc_index + (short)(options->dir[0]);
	new_pc->next = &(player->pc);
	player->pc = *new_pc;
}