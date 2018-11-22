/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 06:34:11 by achernys          #+#    #+#             */
/*   Updated: 2018/11/22 14:16:22 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void		check_num_flag(unsigned int *dest, char **argv, int arg,
		char sign)
{
	int i;

	i = 0;
	if (argv[arg][i] == '-' || argv[arg][i] == '+')
		i++;
	while (ft_isdigit(argv[arg][i]) == 1)
		i++;
	if (argv[arg][i] != '\0')
		print_usage();
	if ((i == 0 || (i == 1 && ft_strncmp(argv[arg], "-", 1) == 0) ||
			(i == 1 && ft_strncmp(argv[arg], "+", 1) == 0)))
		print_usage();
	if (ft_atoi(argv[arg]) < 0)
		print_usage();
	if (sign == 1)
		*dest = (unsigned)-ft_atoi(argv[arg]);
	else
		*dest = (unsigned)ft_atoi(argv[arg]);
}

static char	flags_definition(t_data_prog *data_prog, char **argv, int argc,
		int *using_args)
{
	if (*using_args != argc && ft_strcmp(argv[*using_args], "-dump") == 0)
	{
		if (++(*using_args) == argc)
			print_usage();
		check_num_flag((unsigned *)&(data_prog->game_info->stop_game),
				argv, *using_args, 0);
	}
	else if (*using_args != argc && ft_strcmp(argv[*using_args], "-s") == 0)
	{
		if (++(*using_args) == argc)
			print_usage();
		check_num_flag((unsigned *)&(data_prog->game_info->flag_s),
								argv, *using_args, 0);
	}
	else if (*using_args != argc && ft_strcmp(argv[*using_args], "-m") == 0)
		data_prog->game_info->flag_m = 1;
	else if (*using_args != argc && ft_strcmp(argv[*using_args], "-i") == 0)
		data_prog->game_info->flag_i = 1;
	else if (*using_args != argc && ft_strcmp(argv[*using_args], "-pc") == 0)
		data_prog->game_info->flag_pc = 1;
	else
		return (1);
	return (0);
}

int			get_flags(t_data_prog *data_prog, char **argv, int argc)
{
	int using_args;

	using_args = 1;
	while (using_args < argc)
	{
		if (flags_definition(data_prog, argv, argc, &using_args))
			return (using_args);
		using_args++;
	}
	return (using_args);
}
