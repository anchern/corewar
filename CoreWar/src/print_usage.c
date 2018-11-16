/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 07:09:47 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 09:49:53 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/mylib/ft_printf.h"
#define USAGE_EXIT 75

void	print_usage(void)
{
	ft_printf("{green}Usage:{eoc} ./corewar [-dump N -s N -m -i -pc] "
		   "[[-n number] champion1.cor] ...\n");
	ft_printf("\t-dump N\t: Dumps memory after N cycles then exits\n"
			  "\t-s N\t: Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("\t-m\t\t: Print columns number\n");
	ft_printf("\t-i\t\t: Show cycles\n");
	ft_printf("\t-pc\t: Show process information\n");
	exit(USAGE_EXIT);

}
