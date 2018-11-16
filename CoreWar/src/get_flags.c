/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 06:34:11 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 11:33:47 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static char	flags_definition(t_data_prog *data_prog, char **argv, int argc,
		int *using_args)
{
	if (*using_args != argc && ft_strcmp(argv[*using_args], "-dump") == 0)
	{
		if (++(*using_args) == argc)
			print_usage();
		data_prog->game_info->stop_game = ft_atoi(argv[*using_args]);
	}
	else if (*using_args != argc && ft_strcmp(argv[*using_args], "-s") == 0)
	{
		if (++(*using_args) == argc)
			print_usage();
		data_prog->game_info->flag_s = ft_atoi(argv[*using_args]);
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
