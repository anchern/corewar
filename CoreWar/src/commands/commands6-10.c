#include "../../inc/vm.h"

void	and_function(t_options *options, t_player *player)
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
		a = (unsigned int)(options->ind[0]);
	if (options->option_number[1] == 1)
		a = player->registry[options->reg[1] - 1];
	else if (options->option_number[0] == 2)
		a = options->dir[1];
	else if (options->option_number[0] == 3)
		a = (unsigned int)(options->ind[1]);
	player->registry[options->reg[2] - 1] = a & b;
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
}

void	or_function(t_options *options, t_player *player)
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
		a = (unsigned int)(options->ind[0]);
	if (options->option_number[1] == 1)
		a = player->registry[options->reg[1] - 1];
	else if (options->option_number[0] == 2)
		a = options->dir[1];
	else if (options->option_number[0] == 3)
		a = (unsigned int)(options->ind[1]);
	player->registry[options->reg[2] - 1] = a | b;
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
}

void	xor_function(t_options *options, t_player *player)
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
		a = (unsigned int)(options->ind[0]);
	if (options->option_number[1] == 1)
		a = player->registry[options->reg[1] - 1];
	else if (options->option_number[0] == 2)
		a = options->dir[1];
	else if (options->option_number[0] == 3)
		a = (unsigned int)(options->ind[1]);
	player->registry[options->reg[2] - 1] = a ^ b;
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
}

void	jump_function(t_options *options, t_player *player)
{
	if (player->carry == 1)
		player->pc.pc_index += (options->dir[0] % IDX_MOD);
}

void	load_index_function(t_options *options, t_player *player, t_sell *field)
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
	player->registry[options->reg[2] - 1] = bytestoui(field, player->pc.pc_index + (short)((a + b)%IDX_MOD));
}
