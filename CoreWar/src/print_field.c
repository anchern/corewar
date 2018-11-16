/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 06:22:24 by achernys          #+#    #+#             */
/*   Updated: 2018/11/16 08:14:59 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static void	print_top_marking(void)
{
	int		i;

	i = 0;
	ft_printf("%9c", ' ');
	while (i < 64)
	{
		ft_printf("%02x ", i);
		i++;
	}
	ft_printf("\n");
	i = 0;
	while (i < 64 * 3 + 8)
	{
		ft_printf("-");
		i++;
	}
	ft_printf("\n");
}

void		print_field(t_game_info *game_info)
{
	int		i;

	i = 0;
	if (game_info->flag_m == 1)
		print_top_marking();
	ft_printf("0x0000 : ");
	while (i < FIELD_SIZE)
	{
		ft_printf("%02x", game_info->field[i].value);
		if (!((i + 1) % 64))
		{
			ft_printf("\n");
			if (i != FIELD_SIZE - 1)
				ft_printf("%#06x : ", i + 1);
		}
		else
			ft_printf(" ");
		i++;
	}
}
