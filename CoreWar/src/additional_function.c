/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 02:56:18 by achernys          #+#    #+#             */
/*   Updated: 2018/10/24 09:01:05 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

short		true_value_pc_index(short pc_index)
{
	if (pc_index == FIELD_SIZE)
		return (0);
	if (pc_index < 0)
	{
		while (pc_index < 0)
			pc_index += (short)FIELD_SIZE;
		return (pc_index);
	}
	if (pc_index >= FIELD_SIZE)
		return (pc_index % (short)FIELD_SIZE);
	return (pc_index);
}

t_player	*find_player_by_number(t_player *first_player,
		unsigned desired_number)
{
	if (first_player == 0)
		return (0);
	if (first_player->player_number == desired_number)
		return (first_player);
	return (find_player_by_number(first_player->next, desired_number));
}
