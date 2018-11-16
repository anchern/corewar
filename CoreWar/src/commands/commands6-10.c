#include "../../inc/vm.h"

void			dop_and_function(t_data_prog *data_prog, unsigned int *result,
		unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(*result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		(*result) += 4;
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		(*result) += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index + data_prog->pc->options->ind[1]);
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] = a & b;
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
}

unsigned int	and_function(t_data_prog *data_prog)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;
	
	a = 0;
	b = 0;
	result = 3;
	if (data_prog->pc->options->option_number[0] == 1)
	{
		result++;
		a = data_prog->pc->registry[data_prog->pc->options->reg[0] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 4;
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
		+ data_prog->pc->options->ind[0]);
		result += 2;
	}
	dop_and_function(data_prog, &result, a, b);
	return (result);
}

void			dop_or_function(t_data_prog *data_prog, unsigned int *result,
					unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(*result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		(*result) += 4;
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		(*result) += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
		+ data_prog->pc->options->ind[1]);
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] = a | b;
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
}

unsigned int	or_function(t_data_prog *data_prog)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;
	
	a = 0;
	b = 0;
	result = 3;
	if (data_prog->pc->options->option_number[0] == 1)
	{
		result++;
		a = data_prog->pc->registry[data_prog->pc->options->reg[0] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 4;
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index
		+ data_prog->pc->options->ind[0]);
		result += 2;
	}
	dop_or_function(data_prog, &result, a, b);
	return (result);
}

void			dop_xor_function(t_data_prog *data_prog, unsigned int *result,
			unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(*result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		(*result) += 4;
		b = data_prog->pc->options->dir[1];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		(*result) += 2;
		b = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
		data_prog->pc->options->ind[1]);
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] = a ^ b;
	if (data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] == 0)
		data_prog->pc->carry = 1;
	else
		data_prog->pc->carry = 0;
}

unsigned int	xor_function(t_data_prog *data_prog)
{
	unsigned int a;
	unsigned int b;
	unsigned int result;
	
	a = 0;
	b = 0;
	result = 3;
	if (data_prog->pc->options->option_number[0] == 1)
	{
		result++;
		a = data_prog->pc->registry[data_prog->pc->options->reg[0] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 4;
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
		data_prog->pc->options->ind[0]);
		result += 2;
	}
	dop_xor_function(data_prog, &result, a, b);
	return (result);
}

unsigned int	dop_load_index_function(t_data_prog *data_prog, unsigned int
result, unsigned int a, unsigned int b)
{
	if (data_prog->pc->options->option_number[1] == 1)
	{
		(result)++;
		b = data_prog->pc->registry[data_prog->pc->options->reg[1] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 2;
		data_prog->pc->options->dir[1] = (short)data_prog->pc->options->dir[1];
		b = data_prog->pc->options->dir[1];
	}
	data_prog->pc->registry[data_prog->pc->options->reg[2] - 1] =
			bytestoui(data_prog->game_info->field,
					data_prog->pc->pc_index +
					(short)((short)(a + b) % IDX_MOD));
	return (result);
}

unsigned int	load_index_function(t_data_prog *data_prog)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	result;
	
	a = 0;
	b = 0;
	result = 3;
	if (data_prog->pc->options->option_number[0] == 1)
	{
		result++;
		a = data_prog->pc->registry[data_prog->pc->options->reg[0] - 1];
	}
	else if (data_prog->pc->options->option_number[0] == 2)
	{
		result += 2;
		data_prog->pc->options->dir[0] = (short)data_prog->pc->options->dir[0];
		a = data_prog->pc->options->dir[0];
	}
	else if (data_prog->pc->options->option_number[0] == 3)
	{
		result += 2;
		a = bytestoui(data_prog->game_info->field, data_prog->pc->pc_index +
			(short)(data_prog->pc->options->ind[0] % IDX_MOD));
	}
	return (dop_load_index_function(data_prog, result, a, b));
}
