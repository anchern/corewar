#include "../../inc/vm.h"

unsigned int	and_function(t_options *options, t_player *player)
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
		result += 4;
		a = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		a = (unsigned int) (options->ind[0]);
		result += 2;
	}
	if (options->option_number[1] == 1)
	{
		result++;
		a = player->registry[options->reg[1] - 1];
	}
	else if (options->option_number[0] == 2)
	{
		result += 4;
		a = options->dir[1];
	}
	else if (options->option_number[0] == 3)
	{
		result += 2;
		a = (unsigned int) (options->ind[1]);
	}
	player->registry[options->reg[2] - 1] = a & b;
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (result);
}

unsigned int	or_function(t_options *options, t_player *player)
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
		result += 4;
		a = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		a = (unsigned int) (options->ind[0]);
		result += 2;
	}
	if (options->option_number[1] == 1)
	{
		result++;
		a = player->registry[options->reg[1] - 1];
	}
	else if (options->option_number[0] == 2)
	{
		result += 4;
		a = options->dir[1];
	}
	else if (options->option_number[0] == 3)
	{
		result += 2;
		a = (unsigned int) (options->ind[1]);
	}
	player->registry[options->reg[2] - 1] = a | b;
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (result);
}

unsigned int	xor_function(t_options *options, t_player *player)
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
		result += 4;
		a = options->dir[0];
	}
	else if (options->option_number[0] == 3)
	{
		a = (unsigned int) (options->ind[0]);
		result += 2;
	}
	if (options->option_number[1] == 1)
	{
		result++;
		a = player->registry[options->reg[1] - 1];
	}
	else if (options->option_number[0] == 2)
	{
		result += 4;
		a = options->dir[1];
	}
	else if (options->option_number[0] == 3)
	{
		result += 2;
		a = (unsigned int) (options->ind[1]);
	}
	player->registry[options->reg[2] - 1] = a ^ b;
	if (player->registry[options->reg[2] - 1] == 0)
		player->carry = 1;
	else
		player->carry = 0;
	return (result);
}

unsigned int	jump_function(t_options *options, t_player *player)
{
	if (player->carry == 1)
		return  (unsigned)((int)options->dir[0] % IDX_MOD);
	else
		return (1);
}

unsigned int	load_index_function(t_options *options, t_player *player, t_sell *field)
{
	unsigned int 	a;
	unsigned int 	b;
	unsigned int	result;

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
			player->pc->pc_index + (short)((a + b) % IDX_MOD));
	return (result);
}
