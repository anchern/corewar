/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 07:09:47 by achernys          #+#    #+#             */
/*   Updated: 2018/11/22 13:32:14 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/mylib/ft_printf.h"
#define USAGE_EXIT 75

void	print_usage(void)
{
	ft_printf("{green}Usage:{eoc} ./corewar [-dump N -s N -m -i -pc] "
		"[[-n number] champion1.cor] ...\n");
	ft_printf("\tEvery N must be more or equal than 0\n");
	ft_printf("\t-dump N\t: Dumps memory after N cycles then exits\n"
			"\t-s N\t: Runs N cycles, dumps memory, pauses, then repeats.\n"
					"\t\t\t\tCan be update N while pause\n");
	ft_printf("\t-m\t\t: Print columns number\n");
	ft_printf("\t-i\t\t: Show cycles\n");
	ft_printf("\t-pc\t\t: Show process information\n");
	exit(USAGE_EXIT);
}
